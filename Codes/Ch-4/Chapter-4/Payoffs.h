// This file is licensed under the Mozilla Public License, v. 2.0.
// You can obtain a copy of the license at http://mozilla.org/MPL/2.0/.

#pragma once
#include <memory>

// Payoff (C++11/C++14) -- from Ch 3

class Payoff
{
public:
	//virtual double operator()(double price) const = 0;
	virtual double payoff(double price) const = 0;
	virtual std::unique_ptr<Payoff> clone() const = 0;
	virtual ~Payoff() = default;
};

class CallPayoff final : public Payoff
{
public:
	CallPayoff(double strike);
	double payoff(double price) const override;
	std::unique_ptr<Payoff> clone() const override;		// clone() now returns a unique_ptr<Payoff>,
	// not unique_ptr<CallPayoff>

private:
	double strike_;
};

class PutPayoff final : public Payoff
{
public:
	PutPayoff(double strike);
	double payoff(double price) const override;
	std::unique_ptr<Payoff> clone() const override;		// clone() now returns a unique_ptr<Payoff>,
	// not unique_ptr<PutPayoff>

private:
	double strike_;
};