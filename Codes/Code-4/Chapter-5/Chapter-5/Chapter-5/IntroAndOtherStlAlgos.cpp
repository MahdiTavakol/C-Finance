
#include "StlAlgorithms.h"

#include <vector>
#include <deque>
#include <list>
#include <array>
#include <set>
#include <map>
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

void intro_and_other_stl_algos()
{
	first_example_count_if();
	first_ex_with_other_containers();
	first_ex_with_ranges();
}

bool is_odd(int n)
{
	return n % 2 != 0;
}

void first_example_count_if()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** first_example_count_if() ***\n";

	vector<int> int_vec{ 1,2,3,4,5,6,7,8,9 };

	int count = 0;
	for (int k : int_vec)
	{
		if (k % 2 != 0)
		{
			++count;
		}
	}

	cout << "\nBrute force for loop results:\n";
	cout << format("Number of odd elements = {}\n\n", count);

	count = 0;
	for (int k : int_vec)
	{
		if (is_odd(k)) count++;
	}

	cout << "\nUSing loop with is_odd(.) predicate function -- results:\n";
	cout << format("Number of odd elements = {}\n\n", count);

	auto num_odd = std::count_if(int_vec.begin(), int_vec.end(), is_odd);

	cout << "Type for num_add: " << typeid(num_odd).name() << "\n";
	cout << "\nUsing std::count_if algorithm with is_odd(.) auxiliary function -- results:\n";
	cout << format("Number of odd_elements={}\n\n", num_odd);

	auto num_even = std::count_if(int_vec.begin(), int_vec.end(), [](int n) {return !is_odd(n); });

	const int rem = 2;
	auto num_congruent_mod_3 = std::count_if(int_vec.begin(), int_vec.end(), [&rem](int n) {return n % 3 == rem; });

	auto num_within_interval = std::count_if(int_vec.begin(), int_vec.end(), [low = 3, high = 6](int n) {return low <= n && n <= high; });

	cout << format("num_even = {}, num_congruent_mod_3 = {}, num_within_interval [3,6] = {}\n", num_even, num_congruent_mod_3, num_within_interval);

}

void first_ex_with_other_containers()
{
	using std::vector, std::cout, std::format;
	cout << "\n *** first_ex_with_other_containers() ***\n";

	std::list<int> int_list{ 1,2,3,4,5,6,7,8,9 };
	auto num_odd = std::count_if(int_list.begin(), int_list.end(), is_odd);
	cout << format("num_odd = {} (std::list)\n", num_odd);

	std::set<int> int_set{ 1,2,3,4,5,6,7,8,9 };
	num_odd = std::count_if(int_set.begin(), int_set.end(), is_odd);
	cout << format("num_odd = {} (std::set)\n", num_odd);

	auto is_odd_value = [](const std::pair<unsigned, int>& a_pair) -> bool {
		return is_odd(a_pair.second);
		};

	std::map<unsigned, int> int_map{ {1, 9}, {2, 8}, {3, 7}, {4, 6}, {5, 5}, {6, 4},
		{7, 3}, {8, 2}, {9, 1} };

	num_odd = std::count_if(int_map.begin(), int_map.end(), is_odd_value);
	cout << format("num_odd = {} (std::map)\n");

	std::unordered_map<unsigned, int> int_unord_map{ {1, 9}, {2, 8}, {3, 7}, {4, 6},
	{5, 5}, {6, 4}, {7, 3}, {8, 2}, {9, 1} };
	num_odd = std::count_if(int_unord_map.begin(), int_unord_map.end(), is_odd_value);
	cout << format("num_odd = {} (std::unordered_map)\n\n", num_odd);

}

void first_ex_with_ranges()
{
	using std::vector, std::cout, std::format;
	cout << "\n *** first_ex_with_ranges() ***\n";

	std::vector<int> int_vec{ 1,2,3,4,5,6,7,8,9 };
	std::list<int> int_list{ 1,2,3,4,5,6,7,8,9 };

	auto num_odd = std::ranges::count_if(int_vec, is_odd);
	cout << format("num_odd = {} (std::vector, using ranges\n", num_odd);

	num_odd = std::ranges::count_if(int_list, is_odd);
	cout << format("num_odd = {} (std::list, using ranges\n", num_odd);

}
