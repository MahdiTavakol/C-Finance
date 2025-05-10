#include "StlAlgorithms.h"
#include "UserDefinedTemplates.h"


#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iostream>
#include <format>
#include <iomanip>

void range_view_examples()
{
	indiv_views();
	chain_views();
	range_based_views();
	views_containers_loops();
}

void indiv_views()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** indiv_views() ***\n\n";

	std::vector<double> w(10);
	std::iota(w.begin(), w.end(), -5.5);
	cout << "Original vector w:\n";
	for (double x : w)
	{
		print_this(x);
	}

	print_this("\n\n");

	auto take_five = std::views::take(w, 5);
	auto two_below = std::views::filter(take_five, [](double x) {return x < -2.0; });
	auto squares = std::views::transform(two_below, [](double x) {return x * x; });
	auto drop_two = std::views::drop(squares, 2);

	print_this(typeid(take_five).name());
	print_this("\n\n");

	auto print_range = [](auto rng)
		{
			for (double x : rng) { print_this(x); }
		};

	print_this("In order: take_five, two_below, squares, drop_two:\n");
	print_range(take_five);
	print_this("\n");
	print_range(two_below);
	print_this("\n");
	print_range(squares);
	print_this("\n");
	print_range(drop_two);
	print_this("\n\n");
}

void chain_views()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** chain_views() ***\n\n";

	std::vector<double> w(10);
	std::iota(w.begin(), w.end(), -5.5);
	cout << "Original vector w:\n";
	for (double x : w) { print_this(x); }
	print_this("\n\n");

	auto drop_two = w | std::views::take(5)
		| std::views::filter([](double x) {return x < -2.0; })
		| std::views::transform([](double x) {return x * x; })
		| std::views::drop(2);

	auto print_range = [](auto rng)
		{
			for (double x : rng) { print_this(x); }
		};

	print_range(drop_two);
	print_this("\n\n");

}

void range_based_views()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** range_based_views() ***\n";

	std::vector<double> w(10);
	std::iota(w.begin(), w.end(), -5.5);

	auto take_five = std::views::take(w, 5);

	std::vector<double> u;
	u.reserve(take_five.size());

	for (auto x : take_five)
	{
		u.push_back(x);
	}

	for (auto x : w | std::views::take(5))
	{
		print_this(x);
	}
	print_this("\n\n");

	for (auto x : w | std::views::take(5)
		| std::views::transform([](double x) {return x * x; }))
	{
		print_this(x);
	}

	print_this("\n\n");
}

void views_containers_loops()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** views_containers_loops() ***\n\n";

	// Start with the same data as before:
	std::vector<double> w(10);
	std::iota(w.begin(), w.end(), -5.5);

	auto take_five = std::views::take(w, 5);

	std::vector<double> u;
	u.reserve(take_five.size());
	for (auto x : take_five)
	{
		u.push_back(x);
	}

	for (auto x : u)
	{
		print_this(x);
	}
	print_this("\n\n");

	for (auto x : w | std::views::take(5))
	{
		print_this(x);
	}

	cout << "\n\n";

	for (auto x : w | std::views::take(5)
		| std::views::transform([](double x) {return x * x; }))
	{
		print_this(x);
	}
	cout << "\n\n";
}