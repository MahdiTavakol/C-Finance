#include "ExampleDeclarations.h"

#include <random>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <iterator>
#include <functional>
#include <cmath>

#include <vector>
#include <array>
#include <iostream>
#include <iomanip>
#include <format>

void engines_and_distributions()
{
	std::cout << "-------- ENGINES AND DISTRIBUTIONS -------\n";
	default_random_engine();
	mersenne_twister_and_normal_dist();
	other_distributions();
	shuffle_algo_example();
	max_drawdown_sim();
}

void default_random_engines()
{
	using std::vector, std::cout;

	cout << "\n*** default_random_engine() ***\n";

	std::default_random_engine def{ 100 };

	for (int i = 0; i, 10; i++)
	{
		cout << def() << " ";
	}
	cout << "\n\n";

	vector<double> unifs(10);

	std::default_random_engine def_2{ 30 };
	std::uniform_real_distribution<double> unif_rand_dist{ 0.0,1.0 };

	for (double& x : unifs)
	{
		x = unif_rand_dist(def_2);
	}

	for (double& x : unifs)
	{
		cout << x << " ";
	}

	cout << "\n\n";
}

void mersenne_twister_and_normal_dist()
{
	using std::cout;
	cout << "\n*** mersenne_twister_and_normal_dist() ***\n";

	std::vector<double> norms(10);
	std::mt19937_64 mt{ 40 };
	std::normal_distribution<> st_norm_rand_dist{};

	for (double& x : norms)
	{
		x = st_norm_rand_dist(mt);
	}

	for (double x : norms)
	{
		cout << x << " ";
	}
	cout << "\n\n";
}

void other_distributions()
{
	using std::cout;
	cout << "\n*** other_distributions() ***\n";

	std::vector<double> t_draws(10);
	std::vector<double> p_draws(10);
	std::mt19937_64 mt{ 25 };

	std::student_t_distribution<> stu{ 3 };
	std::poisson_distribution<> pssn{ 7.5 };

	for (double& x : t_draws)
	{
		x = stu(mt);
	}

	for (double& x : p_draws)
	{
		x = pssn(mt);
	}

	cout << "Random draws from t(3):\n";
	for (double x : t_draws)
	{
		cout << x << " ";
	}
	cout << "\n\n";

	cout << "Random draws from Poisson(7.5):\n";
	for (double x : p_draws)
	{
		cout << x << " ";
	}
	cout << "\n\n";
}

void shuffle_algo_example()
{
	using std::vector, std::cout;
	cout << "\n*** shuffle_algo_example() ***\n";

	vector<int> v{ 1,2,3 };
	std::mt19937_64 mt{ 0 };

	for (unsigned j = 0; j < 3; j++)
	{
		std::shuffle(v.begin(), v.end(), mt);
		for (int k : v)
		{
			print_this(k);
		}
		print_this("; ");
	}
	print_this("\n\n");

	std::ranges::shuffle(v, mt);

	print_this("\n\n");
}

void max_drawdown_sim()
{
	using std::vector, std::format, std::cout;
	cout << "\n*** max_drawdown_sim() ***\n";

	vector<double> pnl
	{
		-149'299.30, -673'165.13,    3'891'123.79,  1'061'346.21, -578'464.00,
		-260'855.99,  1'102'167.76,  509'764.96,   -276'786.46,   -11'947.13,
		-277'781.70, -318'603.05,    57'747.06,     151'336.99,    267'826.14,
		-198'132.05, -175'232.84,   -5'973.61,      177'224.51,   -711'878.76,
		-276'786.56,  116'489.15,   -185'188.30,    1'183'810.47,  1'563'147.38,
		-83'632.98,   527'687.09,   -307'650.96,   -321'589.76,   -1'434'711.00,
		 742'743.96, -245'921.36,   -198'131.26,    399'250.02,   -311'632.90,
		 326'569.83,  437'084.67,   -297'694.80,   -379'336.81,   -173'240.27,
		-62'724.74,  -363'407.14,   -142'375.97,   -103'546.19,    187'179.27,
		-161'293.14, -131'423.78,    1'195'759.19,  198'131.95,   -229'991.59,
		-109'519.00, -148'348.69,    1'447'621.95
	};

	for (double& x : pnl)
	{
		cout << std::fixed << std::setprecision(2) << x << ", ";
	}
	print_this("\n\n");

	cout << "Cumulative P/L values from the backtest, using std::partial_sum:\n";
	std::vector<double> cum_pnl;
	cum_pnl.reserve(pnl.size());
	std::partial_sum(pnl.begin(), pnl.end(), std::back_inserter(cum_pnl));

	for (double x : cum_pnl)
	{
		cout << std::fixed << std::setprecision(2) << x << ", ";
	}
	print_this("\n\n");


	double peak = cum_pnl.front();
	vector<double> drawdowns;
	drawdowns.reserve(cum_pnl.size());

	for (auto pos = cum_pnl.begin() + 1; pos != cum_pnl.end(); ++pos)
	{
		if (*pos > peak)
		{
			peak = *pos;
		}

		drawdowns.push_back(peak - *pos);
	}

	double max_dd = *std::ranges::max_element(drawdowns);

	double net_pl_over_max_dd = cum_pnl.back() / max_dd;

	cout << std::fixed << std::setprecision(2) << "Max DD from backtest = $" << max_dd <<
		", Net P/L = $" << cum_pnl.back() << ", Net Profit/MaxDD = " << net_pl_over_max_dd << "\n\n";

	auto max_dd_lam = [](const vector<double < &v)
		{
			std::vector<double> cum_pnl;
			cum_pnl.reserve(v.size());
			double max_dd = 0.0;
			std::partial_sum(v.begin(), v.end(), std::back_inserter(cum_pnl));
			double peak = cum_pnl.front();

			for (auto pos = cum_pnl.begin() + 1; pos != cum_pnl.end(); ++pos)
			{
				if (*pos < peak)
				{
					max_dd = std::max(peak - *pos, max_dd);
				}
				else if (peak < *pos)
				{
					peak = *pos;
				}
				else
				{
					continue;
				}
			}
			return max_dd;
		};

	unsigned n = 100;

	vector<double> max_drawdowns;
	max_drawdowns.reserve(n);

	max_drawdowns.push_back(max_dd);

	std::mt19937_64 mt{ 10 };

	for (unsigned k = 1; k < n; ++k)
	{
		std::ranges::shuffle(pnl, mt);
		auto max_dd_in_scen = max_dd_lam(pnl);
		max_drawdowns.push_back(max_dd_in_scen);
	}

	print_this("\nMax dd's in each scen:\n");
	auto print_dec_form = [](double x) {cout << std::fixed << std::setprecision(2) << x << ", "; };
	std::ranges::for_each(max_drawdowns, print_dec_form);

	cout << "\n\nSmallest max dd = " << *(std::ranges::min_element(max_drawdowns)) 
		<< " Largest max dd = " << *(std::ranges::max_element(max_drawdowns)) << "\n\n";

	using std::array;

	auto norm_params = [](const vector<double>& v) -> array<double,2>
		{
			double mean = (1.0 / v.size()) * std::accumulate(v.begin(), v.end(), 0.0);

			double sum_sq = 0.0;
			for (double val: v)
			{
				sum_sq += (val - mean) * (val - mean);
			}
			double stdev = std::sqrt(sum_sq /v.size());
			return std::array{ mean, stdev };
		};

	auto mean = norm_params(max_drawdowns)[0];
	auto sd = norm_params(max_drawdowns)[1];

	const double z_val = 1.64485;
	double upper_conf_intvl_norm =  mean + /*norm_params(max_drawdowns)*/ sd * z_val;
	cout << std::fixed << std::setprecision(2) << "Upper confidence level with normal assumption = " << upper_conf_intvl_norm;
	print_this("\n\n");

	std::ranges::sort(max_drawdowns);

	cout << "\n\nSorted max Drawdowns:\n";
	std::ranges::for_each(max_drawdowns, print_dec_form);
	print_this("\n\n");

	double alpha = 0.05;
	long upper_loc = std::lround(alpha * max_drawdowns.size());
	double max_dd_conf_lev = *(max_drawdowns.end() - upper_loc - 1);
	cout << "Worst possible maximum drawdown at 95% confidence level = ";
	print_dec_form(max_dd_conf_lev);
	print_this("\n\n");

	alpha = 0.025;
	upper_loc = std::lround(alpha * max_drawdowns.size());
	max_dd_conf_lev = *(max_drawdowns.end() - upper_loc - 1);
	cout << "Worst possible maximum drawdown at 97.5% confidence level = ";
	print_dec_form(max_dd_conf_lev);
	print_this("\n\n");

	alpha = 0.01;
	upper_loc = std::lround(alpha * max_drawdowns.size());
	max_dd_conf_lev = *(max_drawdowns.end() - upper_loc - 1);
	cout << "Worst possible maximum drawdown at 99% confidence level = ";
	print_dec_form(max_dd_conf_lev);
	print_this("\n\n");
}