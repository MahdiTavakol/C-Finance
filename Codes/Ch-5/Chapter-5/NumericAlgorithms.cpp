#include "StlAlgorithms.h"
#include "UserDefinedTemplates.h"

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iterator>
#include <functional>
#include <utility>
#include <cmath>

#include <iostream>
#include <format>
#include <iomanip>

void numerical_algorithms()
{
	iota_examples();
	accumulate_and_inner_product_examples();
	adj_diff_examples();
	partial_sum_examples();
	fold_left_examples();
	vwap_example();
	logs_of_adj_diff_divisions();
	adj_diffs_of_logs();
}

void iota_examples()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** iota_examples() ***\n";

	vector<int> v(6);
	vector<double> w(6);

	std::iota(v.begin(), v.end(), 101);
	std::iota(w.begin(), w.end(), -2.5);

	for (int k : v) { print_this(k); }
	print_this("\n\n");

	vector<unsigned> days_in_november(30);
	std::iota(days_in_november.begin(), days_in_november.end(), 1);
	for (int d : days_in_november) { print_this(d); }
	print_this("\n\n");
}

void accumulate_and_inner_product_examples()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** accumulate_and_inner_product_examples() ***\n";

	vector<int> v(6);
	vector<double> w(6);
	std::iota(v.begin(), v.end(), 101);
	std::iota(w.begin(), w.end(), -2.5);

	int sum_of_ints = std::accumulate(v.begin(), v.end(), 0);
	double sum_of_reals = std::accumulate(w.begin(), w.end(), 0.0);

	cout << format("Sum of ints = {}, sum of reals = {}\n\n", sum_of_ints, sum_of_reals);


	double prod_of_reals = std::accumulate(w.begin(), w.end(), 1.0, std::multiplies<double>());
	cout << format("Product of reals = {}\n\n", prod_of_reals);

	vector<int> u(6);
	std::iota(u.begin(), u.end(), -3);
	int dot_prod = std::inner_product(v.begin(), v.end(), u.begin(), 0);
	cout << format("Dot product of v and u ={}\n", dot_prod);

	vector<double> y(w.size());
	std::iota(y.begin(), y.end(), 1.5);
	double sum_diffs = std::inner_product(w.begin(), w.end(), y.begin(), 0.0, std::plus<double>(), std::minus<double>());

	cout << format("inner_product abstracted for sum of differences of w and y = {}\n",
		sum_diffs);
}

void adj_diff_examples()
{
	using std::cout, std::vector;
	cout << "\n***adj_diff_examples()***\n";

	std::vector<int> u{ 100,101,103,106,110,115,121 };
	std::deque<int> adj_diffs;

	std::adjacent_difference(u.begin(), u.end(), std::back_inserter(adj_diffs));

	cout << "\nAdjacent differences with original 1st element in deque:\n";
	for (int diff : adj_diffs)
	{
		cout << diff << " ";
	}
	cout << "\n\n";

	adj_diffs.pop_front();
	cout << "\nAdjacent differences with 1st element removed from front of deque (diff values only):\n";

	for (int diff : adj_diffs)
	{
		cout << diff << " ";
	}
	cout << "\n\n";

	std::deque<double> adj_sums{ -2.5,-1.5,-0.5,0.5,1.5,2.5 };
	std::adjacent_difference(adj_sums.begin(), adj_sums.end(), adj_sums.begin(), std::plus<double>());
	adj_sums.pop_front();
	cout << "\nAdjacent sums using std::adjacent_difference algo with std::plus<double>, 1st element removed from front of deque (diff values only):\n";
	for (double sum : adj_sums)
	{
		cout << sum << " ";
	}
	cout << "\n\n";
}

void partial_sum_examples()
{
	using std::cout, std::vector, std::format;
	cout << "\n***partial_sum_examples()***\n\n";

	vector<int> z{ 10,11,13,16,20,25,31 };
	vector<int> part_sums;
	part_sums.reserve(z.size());
	std::partial_sum(z.begin(), z.end(), std::back_inserter(part_sums));

	for (int ps : part_sums)
	{
		cout << ps << " ";
	}

	cout << "\n\n";

	vector<int> part_prods(z.size());
	std::partial_sum(z.begin(), z.end(), part_prods.begin(), std::multiplies<int>());

	for (int ps : part_prods) { print_this(ps); }
	cout << "\n\n";
}

void fold_left_examples()
{
	using std::cout, std::vector, std::format;
	cout << "\n***std::accumulate functionality in ranges: std::ranges::fold_left_example()***\n\n";

	vector<int> v(6);
	vector<double> w(6);
	std::iota(v.begin(), v.end(), 101);
	std::iota(w.begin(), w.end(), -2.5);

	int sum_of_ints = std::ranges::fold_left(v, 0, std::plus<int>());
	double sum_of_reals = std::ranges::fold_left(w.begin(), w.end(), 0.0, std::plus<double>());

	cout << format("Sum of ints = {}, sum of reals = {}\n",
		sum_of_ints, sum_of_reals);

	double prod_of_reals = std::ranges::fold_left(w, 1.0, std::multiplies<double>());

	cout << format("Product of reals = {}\n\n", prod_of_reals);

}

void vwap_example()
{
	using std::cout, std::vector;
	cout << "\n***vwap_example()***\n\n";

	vector v{ 376000, 365000, 344000, 346000, 345000, 336000, 335000, 339000, 340000, 340000, 343000, 367000, 37400 };
	vector p{ 208.59, 206.93, 207.75, 209.21, 208.58, 208.63, 207.92, 208.87, 208.16, 209.49, 208.53, 209.12, 209.05 };

	double daily_volume = std::accumulate(v.cbegin(), v.cend(), 0.0);
	double raw_wgt_price = std::inner_product(v.cbegin(), v.cend(), p.cbegin(), 0.0);
	double vwap = raw_wgt_price / daily_volume;

	cout << "Hypothetical Boeing (BA) Daily VWAP = " << vwap << "\n\n";		// 208.48
}

void logs_of_adj_diff_divisions()
{
	using std::cout, std::vector;
	cout << "\n***Calculating log returns: logs_of_adj_diff_divisions()***\n\n";

	vector<double> prices
	{
		25.5, 28.0, 30.5, 31.0, 27.5, 31.0, 29.5, 28.5, 37.5,
		33.5, 25.5, 31.5, 26.5, 29.5, 32.5, 34.5, 28.5, 35.5,
		28.5, 29.0, 32.0, 23.5, 27.5, 33.5, 28.0, 28.0, 32.5,
		31.5, 29.0, 33.0, 32.5, 29.5, 34.5
	};

	std::adjacent_difference(prices.begin(), prices.end(), prices.begin(), std::divides<double>());

	std::deque<double> log_rtns(prices.size());
	std::ranges::transform(prices, log_rtns.begin(), [](double x) {return std::log(x); });

	cout << "Remove the first price -- only want the returns:\n";
	log_rtns.pop_front();
	for (double r : log_rtns)
	{
		cout << std::setprecision(3) << r << " ";
	}

	cout << "\n\n";
}

void adj_diffs_of_logs()
{
	using std::cout, std::vector;
	cout << "\n***Calculating log returns: adj_diffs_of_logs()***\n\n";

	vector<double> prices
	{
		25.5, 28.0, 30.5, 31.0, 27.5, 31.0, 29.5, 28.5, 37.5,
		33.5, 25.5, 31.5, 26.5, 29.5, 32.5, 34.5, 28.5, 35.5,
		28.5, 29.0, 32.0, 23.5, 27.5, 33.5, 28.0, 28.0, 32.5,
		31.5, 29.0, 33.0, 32.5, 29.5, 34.5
	};

	std::ranges::transform(prices, prices.begin(), [](double x) {return std::log(x); });

	std::deque<double> log_rtns;
	std::adjacent_difference(prices.begin(), prices.end(), std::back_inserter(log_rtns));

	for (double r : log_rtns)
	{
		cout << r << " ";
	}

	cout << "\n\n";

	cout << "Remove first price -- only want the returns:\n";
	log_rtns.pop_front();

	for (double r : log_rtns)
	{
		cout << std::setprecision(3) << r << " ";
	}

	cout << "\n\n";
}