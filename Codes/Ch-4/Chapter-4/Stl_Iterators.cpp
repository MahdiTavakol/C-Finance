
#include "Ch04_example_functions.h"
#include "UserDefinedTemplates.h"

#include <vector>
#include <deque>
#include <list>
#include <array>
#include <set>
#include <map>
#include <iterator>

#include <iostream>
#include <format>

void std_iterator_examples()
{
	vector_iterators();
	const_iter();
	iterator_based_for_loop();
	iters_on_assoc_containers();
	iter_examples_in_chptr_summary();
}

void vector_iterators()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** vector_iterators()  ***\n";

	vector<int>::iterator pos;

	vector<int> v = { 17,28,12,33,13,10 };

	pos = v.begin();
	int first_elem = *pos;
	print_this(first_elem);
	cout << "\n";

	++pos;
	print_this(*pos);
	cout << "\n";

	*pos = 19;
	print_this(*pos);
	cout << "\n";
	
	pos += 3;
	print_this(*pos);
	cout << "\n";

	--pos;
	--pos;
	print_this(*pos);
	cout << "\n";

	pos -= 2;
	print_this(*pos);
	cout << "\n";

	pos = v.end() - 1;
	print_this(*pos);
	cout << "\n";

	auto auto_pos = v.begin();
	print_this(*auto_pos);
	cout << "\n\n";
}

void const_iter()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** const_iter() ***\n";

	vector<int> w{ 17,28,12,33,13,10 };
	auto cpos = w.cbegin();
	print_this(*cpos);
	cout << "\n";

	++cpos;
	print_this(*cpos);
	cout << "\n\n";
}

void iterator_based_for_loop()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** iterator_based_for_loop()  ***\n";

	std::vector<int> v{ 17, 28, 12, 33, 13, 10 };

	for (auto pos = v.begin(); pos != v.end(); pos++)
	{
		print_this(*pos);
	}
	cout << "\n\n";
}

void iters_on_assoc_containers()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** iters_on_assoc_containers()  ***\n";

	std::map<int, double> toy_map;
	toy_map = { {5, 92.6}, {2, 42.4}, {1, 10.6}, {4, 3.58}, {3, 33.3} };

	auto pos = toy_map.begin();

	print_this(pos->first);
	cout << ": ";
	print_this(pos->second);
	cout << "\n\n";

	++pos;
	pos->second = 100.0;

	for (const auto& pr : toy_map)
	{
		cout << format("{} : {}\n", pr.first, pr.second);
	}

	cout << "\n";

	for (const auto& [k, v] : toy_map)
	{
		cout << format("{} : {}\n", k, v);
	}

	cout << "\n\n";
}

void iter_examples_in_chptr_summary()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** iter_examples_in_chptr_summary()  ***\n";

	std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
	std::map<unsigned,int> m{ {1, 100}, {2, 200}, {3, 300}, {4, 400},
		{5, 500}, {6, 600}, {7, 700}, {8, 800}, {9, 900}, {10, 1000} };

	auto v_iter = v.begin();
	auto m_iter = m.cbegin();

	int v_elem = *v_iter;
	cout << format("v_elem = {}\n", *v_iter);

	++v_iter;
	++v_iter;
	cout << format("*v_iter = {}\n", *v_iter);

	*v_iter = -3;
	cout << format("*v_iter = {}\n", *v_iter);

	--v_iter;
	cout << format("*v_iter = {}\n", *v_iter);

	v_elem = *v_iter;
	cout << format("v_elem = {}\n", v_elem);

	v_iter += 3;
	v_elem = *v_iter;
	cout << format("v_iter += 3 => v_elem = {}\n\n", v_elem);

	++m_iter;
	++m_iter;
	unsigned key = (*m_iter).first;
	int val = (*m_iter).second;
	cout << format("key at 3rd position = {}, val at 3rd position = {}\n", key, val);
	cout << "\n\n";

	++m_iter;
	auto [key_alt, value_alt] = *m_iter;
	cout << format("key (alt) at 4th position = {}, ", key_alt);
	cout << format("val (alt) at 4th position = {}", value_alt);

	cout << "\n\n";


}