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