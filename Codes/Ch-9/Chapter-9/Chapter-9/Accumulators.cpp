#include "ExampleDeclarations.h"

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/accumulators/statistics/rolling_variance.hpp>


#include <Eigen/Dense>

#include <vector>
#include <cmath>
#include <random>
#include <exception>
#include <cstdlib>

#include <format>
#include <iostream>
#include <iomanip>
using std::format;
using std::cout;
using std::endl;
using std::size_t;

namespace bacc = boost::accumulators;

void accumulator_examples()
{
	min_max_accumulator();
	mean_and_var_accumulator();
	intro_rolling_windows();
	bollinger_bands(1.5, 25, 5);
	ma_cross(5, 10, 25);
}

void min_max_accumulator()
{
	cout << "*** min_max_accumulator() ***" << endl;

	bacc::accumulator_set<double, bacc::stats<bacc::tag::min, bacc::tag::max>> acc{};

	acc(5.8);
	acc(-1.7);
	acc(2.9);

	cout << "(" << bacc::extract::min(acc) << "," << bacc::extract::max(acc) << ")" << endl;
	cout << endl;

	acc(524.0);

	cout << "Updated: (" << bacc::extract::min(acc) << "," << bacc::extract::max(acc) << ")" << endl;
}

void mean_and_var_accumulator()
{
	cout << "*** mean_and_var_accumulator() ***" << endl;

	bacc::accumulator_set<double, bacc::stats<bacc::tag::mean, bacc::tag::variance>> mv_acc{};

	mv_acc(1.0);
	mv_acc(2.0);
	mv_acc(3.0);

	cout << "(" << bacc::extract::mean(mv_acc) << "," << bacc::extract::variance(mv_acc) << ")" << endl;

	mv_acc(4.0);
	mv_acc(5.0);

	cout << "(" << bacc::extract::mean(mv_acc) << "," << bacc::extract::variance(mv_acc) << ")" << endl;

	mv_acc(16.0);
	mv_acc(17.0);
	mv_acc(18.0);

	cout << "(" << bacc::extract::mean(mv_acc) << "," << bacc::extract::variance(mv_acc) << ")" << endl;
}

void intro_rolling_windows()
{
	cout << "\n" << "*** intro_rolling_windows() ***\n";
	cout << "\nNote that rolling_variance is based on the sample variance:\n ";

	bacc::accumulator_set<double, bacc::stats<bacc::tag::rolling_mean, bacc::tag::rolling_variance>> roll_acc{ bacc::tag::rolling_window::window_size = 5 };

	roll_acc(1.0);
	roll_acc(2.0);
	roll_acc(3.0);

	cout << bacc::extract::rolling_mean(roll_acc) << ", "
		<< bacc::extract::rolling_variance(roll_acc) << "\n\n";

	roll_acc(4.0);
	roll_acc(5.0);

	cout << bacc::extract::rolling_mean(roll_acc) << ", "
		<< bacc::extract::rolling_variance(roll_acc) << "\n\n";

	roll_acc(16.0);
	roll_acc(17.0);
	roll_acc(18.0);

	cout << bacc::extract::rolling_mean(roll_acc) << ", "
		<< bacc::extract::rolling_variance(roll_acc) << "\n\n";

}

void bollinger_bands(double n, unsigned obs, unsigned win_size)
{
	cout << "*** bollinger_bands(.)***\n";

	using std::vector, Eigen::MatrixXd;

	vector<double> prices
	{
		100.00, 103.49, 102.82, 106.86, 104.91,
		107.38, 107.46, 111.01, 112.01, 114.11,
		116.91, 121.74, 120.04, 120.24, 120.12,
		120.61, 121.31, 119.25, 118.11, 120.36,
		117.36, 119.12, 119.36, 123.54, 123.42
	};

	bacc::accumulator_set<double, bacc::stats<bacc::tag::rolling_mean, bacc::tag::rolling_variance>>
		prices_acc(bacc::tag::rolling_window::window_size = win_size);

	MatrixXd indicators{ prices.size(),4 };


	for (size_t rec = 0; rec < prices.size(); rec++)
	{
		indicators(rec, 0) = prices[rec];
		prices_acc(prices[rec]);
		if (rec >= win_size  - 1)
		{ 
			indicators(rec, 1) = bacc::extract::rolling_mean(prices_acc);
			double dev = n * std::sqrt(bacc::extract::rolling_variance(prices_acc));
			indicators(rec, 2) = indicators(rec, 1) + dev;
			indicators(rec, 3) = indicators(rec, 1) - dev;
		}
		else {
			indicators(rec, 1) = 0.0;
			indicators(rec, 2) = 0.0;
			indicators(rec, 3) = 0.0;
		}
	}

	cout << "Indictor Info (Bollinger Bands): " << endl;
	cout << std::fixed << std::setprecision(2) << indicators << endl << endl;
}



