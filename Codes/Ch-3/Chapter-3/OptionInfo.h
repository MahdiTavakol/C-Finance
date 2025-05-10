#pragma once

#include "Payoffs.h"
#include <algorithm>
#include <memory>

class OptionInfo03
{
public:
	OptionInfo03(const Payoff03* payoff, double time_to_exp);
	~OptionInfo03();

	double option_payoff(double spot) const;
	double time_to_expiration() const;

	//OptionInfo03(const OptionInfo03& rhs) = delete;
	//OptionInfo03& operator=(const OptionInfo03& rhs) = delete;

	OptionInfo03(const OptionInfo03& rhs);
	OptionInfo03& operator=(const OptionInfo03& rhs);

private:
	Payoff03* payoff_ptr_;
	double time_to_exp_;

	void swap(OptionInfo03& rhs);

	//OptionInfo(const OptionInfo& rhs);
	//OptionInfo& operator=(const OptionInfo& rhs);
};

class OptionInfo
{
public:
	OptionInfo(std::unique_ptr<Payoff> payoff, double time_to_exp);
	double option_payoff(double spot) const;
	double time_to_expiration() const;
	void swap(OptionInfo& rhs) noexcept;

	OptionInfo(const OptionInfo& rhs);
	OptionInfo& operator=(const OptionInfo& rhs);

	// Remaining Rule of Five:

	OptionInfo(OptionInfo&& rhs) = default;
	OptionInfo& operator=(OptionInfo&& rhs) = default;
	~OptionInfo() = default;

private:
	std::unique_ptr<Payoff> payoff_ptr_;
	double time_to_exp_;
};

