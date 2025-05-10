#pragma once

#include <cmath>

class BankAccount
{
public:
	BankAccount(double init_value, double continuous_rate):
		init_value_{init_value}, continuous_rate_{continuous_rate} {}

	BankAccount() = default;

	double value(double time) const
	{
		return init_value_ * std::exp(continuous_rate_ * time);
	}

	double operator()(double time) const
	{
		return value(time);
	}

	double init_value() const
	{
		return init_value_;
	}

	double continuous_rate() const
	{
		return continuous_rate_;
	}

private:
	double init_value_{ 1.0 }, continuous_rate_{ 0.0 };
};
