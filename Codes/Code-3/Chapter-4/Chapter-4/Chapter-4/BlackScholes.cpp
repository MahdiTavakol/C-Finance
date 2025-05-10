#include <cmath>
#include <numbers>
#include <algorithm>
#include <iostream>
#include <format>

#include "BlackScholes.h"

using std::format, std::cout;

BlackScholes::BlackScholes(double strike, double spot, double time_to_exp,
	PayoffType payoff_type, double rate, double div) :
	strike_{ strike }, spot_{ spot }, time_to_exp_{ time_to_exp },
	payoff_type_{ payoff_type }, rate_{ rate }, div_{ div } 
{
	// cout << "\n" << "BlackScholes user-defined constructor" << "\n";
}

double BlackScholes::operator()(double vol) const
{
	using std::exp;
	const int phi = static_cast<int>(payoff_type_);

	if (time_to_exp_ > 0.0)
	{
		auto norm_args = compute_norm_args_(vol);
		double d1 = norm_args[0];
		double d2 = norm_args[1];

		auto norm_cdf = [](double x) -> double
		{
			return (1.0 + std::erf(x / std::numbers::sqrt2)) / 2.0;
		};

		double nd_1 = norm_cdf(phi * d1);
		double nd_2 = norm_cdf(phi * d2);
		double disc_fctr = exp(-rate_ * time_to_exp_);

		return phi * (spot_ * exp(-div_ * time_to_exp_) * nd_1 - disc_fctr * strike_ * nd_2);
	}
	else
	{
		return std::max(phi * (spot_ - strike_), 0.0);
	}
}

std::map<RiskValues, double> BlackScholes::risk_values(double vol)
{
	using std::exp, std::sqrt;

	std::map<RiskValues, double> results;
	compute_norm_args_(vol);
	int phi = static_cast<int>(payoff_type_);

	auto norm_args = compute_norm_args_(vol);
	double d1 = norm_args[0];
	double d2 = norm_args[1];

	double nd_1 = norm_cdf_(phi * d1);
	double nd_2 = norm_cdf_(phi * d2);
	double disc_fctr = exp(-rate_ * time_to_exp_);

	auto norm_pdf = [](double x) ->double
		{
			using namespace std::numbers;
			return (inv_sqrtpi / sqrt2) * exp(-x * x / 2.0);
		};

	double delta = phi * exp(-div_ * time_to_exp_) * nd_1;
	double gamma = exp(-div_ * time_to_exp_) * norm_pdf(d1) /
		(spot_ * vol * sqrt(time_to_exp_));
	double vega = spot_ * spot_ * gamma * vol * time_to_exp_;
	double rho = phi * time_to_exp_ * strike_ * disc_fctr * nd_2;
	double theta = phi * div_ * spot_ * exp(-div_ * time_to_exp_) * nd_1
		- phi * rate_ * strike_ * exp(-rate_ * time_to_exp_) * nd_2
		- spot_ * exp(-div_ * time_to_exp_) * norm_pdf(d1)
		* vol / (2.0 * sqrt(time_to_exp_));

	results.insert({ RiskValues::Delta,delta });
	results.insert({ RiskValues::Gamma,gamma });
	results.insert({ RiskValues::Vega,vega });
	results.insert({ RiskValues::Vega,vega });
	results.insert({ RiskValues::Rho,rho });
	results.insert({ RiskValues::Theta,theta });

	return results;
}

std::array<double, 2> BlackScholes::compute_norm_args_(double vol) const
{
	double numer = log(spot_ / strike_) + (rate_ - div_+0.5*vol*vol)*time_to_exp_;
	double d1 = numer / (vol * sqrt(time_to_exp_));
	double d2 = d1 - vol * sqrt(time_to_exp_);
	return std::array<double, 2>{d1, d2};
}

double BlackScholes::norm_cdf_(double x) const
{
	return (1 + std::erf(x / std::numbers::sqrt2)) / 2.0;
}

double implied_volatility(const BlackScholes& bsc,
	double opt_mkt_price, double x0, double x1, double tol,
	unsigned max_iter)
{
	auto f = [&bsc, opt_mkt_price](double x) ->double
		{
			return bsc(x) - opt_mkt_price;
		};

	double y0 = f(x0);
	double y1 = f(x1);

	double impl_vol = 0.0;
	unsigned count_iter = 0;

	for (; count_iter <= max_iter; ++count_iter)
	{
		if (std::abs(x1 - x0) > tol)
		{
			impl_vol = x1 - (x1 - x0) * y1 / (y1 - y0);

			x0 = x1;
			x1 = impl_vol;
			y0 = y1;
			y1 = f(x1);
		}
		else
		{
			return x1;
		}
	}
	return std::nan("");
}
