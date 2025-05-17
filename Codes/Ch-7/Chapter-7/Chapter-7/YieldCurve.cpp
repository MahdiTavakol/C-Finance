
#include "YieldCurve.h"
#include <stdexcept>
#include <cstddef>
#include <cmath>

YieldCurve::YieldCurve(ChronoDate settle_date) : settle_{ std::move(settle_date) } {}

ChronoDate YieldCurve::settle_date() const
{
	return settle_;
}

Act365 YieldCurve::act_365() const
{
	return act_365_;
}

double YieldCurve::discount_factor(const ChronoDate& date_01, const ChronoDate& date_02) const
{
	using std::exp;

	if (date_02 < date_01)
	{
		throw std::invalid_argument
		{ "YieldCurve::discount_factor(.): dates must fall on or after settle date" };
	}

	if (date_01 == date_02)
	{
		return 1.0;
	}

	double t2 = act_365().year_fraction(settle_date(), date_02);
	double y2 = yield_curve_(t2);

	if (date_01 == settle_date())
	{
		return exp(-t2 * y2);
	}

	double t1 = act_365().year_fraction(settle_date(), date_01);
	double y1 = yield_curve_(t1);

	return exp(t1 * y1 - t2 * y2);
}

LinearInterpYieldCurve::LinearInterpYieldCurve(const ChronoDate& settle_date,
	const std::vector<ChronoDate>& maturity_dates,
	const std::vector<double>& unit_prices) : YieldCurve{ settle_date }
{
	using std::size_t;

	if (maturity_dates.size() != unit_prices.size())
		throw std::invalid_argument{
			"LinearInterpYieldCurve: maturity_dates and spot_discount_factors different lengths" };

	if (maturity_dates.front() < this->settle_date())
		throw std::invalid_argument{ "LinearInterpYieldCurve: first maturity date before settle date" };

	maturities_.reserve(maturity_dates.size());
	yields_.reserve(maturity_dates.size());

	for (size_t i = 0; i < maturity_dates.size(); i++)
	{
		double t = act_365().year_fraction(this->settle_date(), maturity_dates[i]);
		maturities_.push_back(t);
		yields_.push_back(-std::log(unit_prices[i]) / t);
	}
}

double LinearInterpYieldCurve::yield_curve_(double t) const
{
	using std::size_t;

	if (t >= maturities_.back())
	{
		return yields_.back();
	}

	size_t indx = 0;
	while (maturities_[indx + 1] < t)
	{
		indx++;
	}

	return yields_[indx] +
		((yields_[indx + 1] - yields_[indx]) / (maturities_[indx + 1] - maturities_[indx])) * (t - maturities_[indx]);
}