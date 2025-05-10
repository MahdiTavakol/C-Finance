#pragma once


#include <vector>
#include <random>

class EquityPriceGenerator
{
	EquityPriceGenerator(double spot, int num_time_steps,
		double time_to_expiration, double volatility, double rf_rate, double div_rate);

	std::vector<double> operator()(int seed) const;

private:
	double spot_;
	int num_time_steps_;
	double time_to_expiration_;
	double volatility_;
	double rf_rate_;
	double div_rate_;
	double dt_;

};