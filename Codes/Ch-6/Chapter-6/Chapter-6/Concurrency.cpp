#include "ExampleDeclarations.h"

#include <vector>
#include <future>
#include <algorithm>
#include <numeric>
#include <random>
#include <execution>
#include <utility>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <format>

void concurrency_examples()
{
	squares();
}

void squares()
{
	using std::cout, std::format;
	cout << "\n" << "*** squares() ***\n";

	auto square_val = [](int x) {
		return x * x;
		};

	int i = 5;
	auto ftr = std::async(square_val, i);
	cout << std::format("Square of {} is {}\n\n", i, ftr.get());

	std::vector<int> x(25);
	std::iota(x.begin(), x.end(), 1);
	std::vector<std::future<int>> v;

	for (auto k : x)
	{
		v.push_back(std::async(square_val, k));
	}

	std::vector<int> y(v.size());
	std::ranges::transform(v, y.begin(),
		[](std::future<int>& fut)
		{
			return fut.get();
		});

	cout << "Results using a 'vector' of 'future' types (vector<future>):\n";
	for (int k : y)
	{
		print_this(k);
	}
	print_this("\n\n");
}