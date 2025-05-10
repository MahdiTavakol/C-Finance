#include "Ch04_example_functions.h"
#include "Shapes.h"

#include <vector>
#include <deque>
#include <list>
#include <array>
#include <map>
#include <set>
#include <unordered_map>

#include <iostream>
#include <format>

void other_sequential_stl_containers()
{
	deque_examples();
	list_examples();
	std_array_examples();
}

void deque_examples()
{
	using std::cout;
	cout << "\n*** deque_examples()  ***\n";

	std::deque<int> on_deque{ 0,1,2,3 };

	on_deque.push_front(-1);
	on_deque.push_front(-2);

	on_deque.push_back(4);
	for (int k : on_deque)
	{
		cout << k << ' ';
	}

	cout << "\n\n";

	on_deque.pop_front();
	on_deque.pop_back();
	for (int k : on_deque)
	{
		cout << k << ' '; // on_deque now contains: -1 0 1 2 3
	}

	cout << "\n\n";

	std::deque<Rectangle> recs;
	recs.emplace_front(3.0, 2.0);
	recs.emplace_front(4.0, 3.0);
	recs.emplace_front(5.0, 4.0);

	for (const auto& elem : recs)
	{
		cout << elem.area() << " ";
	}

	cout << "\n\n";
}

void list_examples()
{
	using std::cout;
	cout << "\n*** list_examples()  ***\n";

	std::list<int> franz{ 0,1,2,3 };
	for (int elem : franz)
	{
		cout << elem << " ";
	}

	cout << "\n\n";

	franz.push_front(-1);
	franz.push_back(4);
	franz.push_back(5);
	franz.pop_back();

	for (int elem : franz)
	{
		cout << elem << " ";
	}

	cout << "\n\n";
}

void std_array_examples()
{
	using std::cout, std::format;
	cout << "\n*** std_array_examples()  ***\n";

	int arr_01[]{ 0,1,2,3 };
	int sum = 0;
	
	for (int x : arr_01)
	{
		sum += x;
	}

	cout << format("sum (C array) = {}\n", sum);		// = 6

	std::array<int, 4> arr_02{ 0,1,2,3 };
	sum = 0;
	for (int elem : arr_02)
	{
		sum += elem;
	}


	cout << format("sum (std::array) = {}\n", sum);		// = 6

	cout << "\n\n";
}