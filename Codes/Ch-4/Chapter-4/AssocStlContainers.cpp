#include "Ch04_example_functions.h"
#include "BlackScholes.h"
#include <map>
#include <set>
#include <unordered_map>

#include <format>
#include <iostream>

void assoc_stl_containers()
{
	std_set_and_map_examples();
	maps_and_black_scholes();
}

void std_set_and_map_examples()
{
	using std::cout, std::format;
	cout << "\n*** std_set_and_map_examples()  ***\n";

	std::set<int> some_set{ 5,1,2,3,4,3 };
	for (int n : some_set)
	{
		cout << n << " ";
	}

	std::cout << "\n\n";

	std::map<std::string, int> some_map
	{
		{ "five", 5 }, { "one", 1 }, { "two", 2 },
		{ "three", 3 }, { "four", 4 }, { "three", -3 }
	};

	for (auto [k, v] : some_map)
	{
		cout << k << ": " << v << ";";
	}

	std::cout << "\n\n";

	int four = some_map["four"];
	cout << format("Value for index 'four' = {}\n\n", four);

	std::multiset<int> some_multiset{ 5,1,2,3,4,3 };
	for (int n : some_multiset)
	{
		std::cout << n << " ";
	}

	std::cout << "\n\n";

	std::multimap<std::string, int> some_multimap
	{
		{"five", 5}, {"one", 1}, {"two", 2},
		{"three", 3}, {"four", 4}, {"three", -3}
	};

	for (auto [k, v] : some_multimap)
	{
		cout << k << ": " << v << ";";
	}

	cout << "\n\n";
}

void maps_and_black_scholes()
{
	using std::cout, std::format;
	cout << "\n*** maps_and_black_scholes()  ***\n";

	double strike = 75.0;
	auto corp = PayoffType::Call;
	double spot = 100.0;
	double rate = 0.05;
	double vol = 0.25;
	double time_to_exp = 0.3;
	double div = 0.07;

	cout << "\n" << "OTM Put option with time value, and risk values:" << "\n";

	corp = PayoffType::Put;


	BlackScholes bsp_otm_tv{ strike,spot,time_to_exp,corp,rate,div };
	cout << "Put option price = "
		<< bsp_otm_tv(vol)
		<< "\n\n";

	auto risk_values = bsp_otm_tv.risk_values(vol);

	for (auto [idx, risk_val] : risk_values)
	{
		cout << risk_val << " ";
	}

	cout << "\n\n";

	double delta = risk_values[RiskValues::Delta];
	double gamma = risk_values[RiskValues::Gamma];
	double vega = risk_values[RiskValues::Vega];
	double rho = risk_values[RiskValues::Rho];
	double theta = risk_values[RiskValues::Theta];


	cout << format(" delta = {}\n gamma = {}\n vega = {}\n rho = {}\n theta = {}\n\n",
		delta, gamma, vega, rho, theta);



}