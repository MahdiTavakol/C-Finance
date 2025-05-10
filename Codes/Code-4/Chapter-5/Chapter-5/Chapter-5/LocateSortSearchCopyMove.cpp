#include "StlAlgorithms.h"
#include "UserDefinedTemplates.h"
#include "Fraction.h"

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

void locate_sort_search_copy_move()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** locate_sort_search_copy_move() ***\n";

	count_and_count_if();
	max_min_elements();
	sorting_values();
	searching_containers();
	binary_search_examples();
	copy_and_move();
}

void count_and_count_if()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** count_and_count_if() ***\n\n";

	vector<int> v{ 1,2,3,4,5,6,7 };

	auto count_val_2 = std::count(v.begin(), v.end(), 2);
	cout << format("Occurences of element 2 with no aux fcn = {}\n", count_val_2);

	auto count_if_val_2 = std::count_if(v.begin(), v.end(), [](int x) {return x == 2; });
	cout << format("Occurences of element 2 with aux fcn = {}\n", count_if_val_2);

	count_val_2 = std::ranges::count(v, 2);
	cout << format("Occurences of element 2 with no aux fcn, ranges version={}\n", count_if_val_2);

	count_if_val_2 = std::ranges::count_if(v, [](int x) {return x == 2; });
	cout << format("Occurences of element 2 with aux fcn, ranges version={}\n", count_if_val_2);
}

void max_min_elements()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** max_min_elems() ***\n";

	vector<int> v = { 6,7,3,5,4,1,2,9,8 };
	auto max_elem = std::max_element(v.begin(), v.end());
	auto min_elem = std::min_element(v.begin(), v.end());

	cout << format("max = {}, min = {}", *max_elem, *min_elem);
	cout << "\n\n";
}

void sorting_values()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** sorting_and_unique_values() ***\n";

	cout << "\nSorting elements in deque:\n";
	std::deque<int> dq{ 6,7,3,5,4,1,2,9,8 };
	std::sort(dq.begin(), dq.end());
	for (int k : dq) print_this(k);
	print_this("\n\n");

	cout << "\nSort elements in deque with ranges version:\n";
	std::vector<int> dq_ranges{ 6,7,3,5,4,1,2,9,8 };
	std::ranges::sort(dq);
	for (int k : dq_ranges) print_this(k);
	print_this("\n\n");

	std::deque<int> dq_aux{ 6,7,3,5,4,1,2,9,8 };
	std::vector<int> v_ranges_aux{ 6,7,3,5,4,1,2,9,8 };

	auto gt = [](int a, int b) {return a > b; };

	std::sort(dq_aux.begin(), dq_aux.end(), gt);
	cout << format("With aux fcn condition (deque):\n");
	for (int k : dq_aux) { print_this(k); }
	print_this("\n\n");

	cout << format("With aux fcn condition an ranges version (vector):\n");
	std::ranges::sort(v_ranges_aux, gt);
	for (int k : v_ranges_aux) { print_this(k); }
	print_this("\n\n");

}

void searching_containers()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** searching_containers() ***\n";

	vector<int> ints{ 747,377,707,757,727,787,777,717,247,737,767 };
	int n = 757;

	auto ipos = std::find(ints.begin(), ints.end(), n);
	if (ipos != ints.end())
	{
		cout << format("Found value {} at index {}\n",
			n, std::distance(ints.begin(), ipos));
	}

	vector<double> reals{ 0.5,1.6,-2.3,0.85,-3.2,2.5,1.8,-0.72 };
	auto rpos = std::find_if(reals.begin(), reals.end(), [](double x) {return x < 0.0; });

	if (rpos != reals.end())
	{
		cout << format("First negative value is {}\n", *rpos);
	}

	ipos = std::ranges::find(ints, n);
	if (ipos != ints.end())
	{
		cout << format("Found value {} at index {} (with std::ranges::find)\n",
			n, std::distance(ints.begin(), ipos));
	}

	rpos = std::ranges::find_if(reals, [](int x) {return x < 0.0; });

	if (rpos != reals.end())
	{
		cout << format("First negative value is {} (with std::ranges::find_if)\n", *rpos);
	}

	cout << "\n\n";
}

void binary_search_examples()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** binary_search_example() ***\n";

	vector<int> ints{ 747, 377, 707, 757, 727, 787, 777, 717, 247, 737, 767 };
	int n = 757;

	std::sort(ints.begin(), ints.end());
	if (std::binary_search(ints.begin(), ints.end(), n))
	{
		cout << format("Found value {}\n", n);
	}

	cout << "\n\n";

	if (std::ranges::binary_search(ints, n))
	{
		cout << format("Found value {} using range version\n", n);
	}

	cout << "\n\n";
}

void copy_and_move()
{
	using std::cout, std::format;
	cout << "\n*** copy_and_move() ***\n";

	std::vector<int> v{ 1,2,3,4,5 };
	std::vector<int> w = v;
	std::transform(w.begin(), w.end(), w.begin(), [](int n) {return -n; });
	for (int n : v)
	{
		std::cout << n << ' ';
	}
	std::cout << "\n";

	std::vector<int> a;

	a.push_back(6);
	a.push_back(7);
	a.push_back(8);
	a.push_back(9);
	a.push_back(10);

	cout << "\nContents of vector a:\n";
	for (int x : a) print_this(x);
	print_this("\n\n");

	a = v;

	cout << "Contents of vector a after copy assignment\n";
	for (int x : a) print_this(x);
	print_this("\n\n");

	std::vector<int> u = std::move(w);

	std::deque<int> dv_copy(std::begin(v), std::end(v));
	std::list<int> list_v_copy(v.begin(), v.end());

	cout << "\nCopy from vector<int> u to deque<int> :\n";
	for (unsigned k : dv_copy)
	{
		print_this(k);
	}
	print_this("\n\n");

	std::deque<int> dv_move;
	std::list<int> list_u_move;

	cout << "\nMove from vector<int> to deque<int>:\n";
	std::move(v.begin(), v.end(), std::back_inserter(dv_move));
	for (unsigned k : dv_move)
	{
		print_this(k);
	}
	print_this("\n\n");

	cout << "\nMove from deque<unsigned> to list<unsigned>:\n";
	std::ranges::move(u, std::back_inserter(list_u_move));
	for (unsigned k : list_u_move)
	{
		print_this(k);
	}
	print_this("\n\n");

	cout << "\nCopy from vector<Fraction> to deque<Fraction>:\n";
	std::vector<Fraction> vec_fracs{ {1, 2}, {5, 8}, {3, 4}, {2, 3}, {1, 9} };
	std::deque<Fraction> dq_fracs(vec_fracs.begin(), vec_fracs.end());

	for (const Fraction& f : dq_fracs)
	{
		cout << format("{}/{}\t", f.numer(), f.denom());
	}
	print_this("\n\n");

	cout << "\nMove from deque<Fraction> to list<Fraction>:\n";
	std::list<Fraction> list_fracs;
	std::ranges::move(dq_fracs, std::back_inserter(list_fracs));

	for (const Fraction& f : list_fracs)
	{
		cout << format("{}/{}\t", f.numer(), f.denom());
	}
	print_this("\n\n");
}