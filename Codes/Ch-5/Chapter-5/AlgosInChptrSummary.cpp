#include "StlAlgorithms.h"

#include <vector>
#include <deque>
#include <array>
#include <set>
#include <algorithm>
#include <ranges>

#include <iostream>
#include <format>

void algo_examples_in_chptr_summary()
{
	using std::cout, std::format;
	cout << "\n*** algo_examples_in_chptr_summary() ***\n\n";
	
	std::array<int, 5> a{ 1,2,3,4,5 };
	std::deque<int> d{ 1,2,3,4,5 };
	std::set<int> s{ 1,2,3,4,5 };
	std::vector<int> v(a.size());

	auto square_that = [](int x) {return x * x; };

	std::transform(a.begin(), a.end(), a.begin(), square_that);
	std::ranges::transform(d, d.begin(), square_that);
	std::transform(s.cbegin(), s.cend(), v.begin(), square_that);

	for (int k : a)
	{
		cout << k << " ";
	}
	cout << "\n\n";

	for (int k : d)
	{
		cout << k << " ";
	}
	cout << "\n\n";

	for (int k : s)
	{
		cout << k << " ";
	}
	cout << "\n\n";

	for (int k : v)
	{
		cout << k << " ";
	}
	cout << "\n\n";
}