#include "Payoffs.h"

#include <algorithm>

CallPayoff03::CallPayoff03(double strike): strike_{strike}{}

CallPayoff03* CallPayoff03::clone() const
{
	return new CallPayoff03(*this);
}

double CallPayoff03::payoff03(double spot) const 
{
	return std::max(spot - strike_, 0.0);
}

PutPayoff03::PutPayoff03(double strike): strike_{strike} {}

double PutPayoff03::payoff03(double spot) const
{
	return std::max(strike_ - spot, 0.0);
}

PutPayoff03* PutPayoff03::clone() const
{
	return new PutPayoff03(*this);
}

CallPayoff::CallPayoff(double strike) : strike_{ strike } {}

double CallPayoff::payoff(double spot) const
{
	return std::max(spot - strike_, 0.0);
}

std::unique_ptr<Payoff> CallPayoff::clone() const
{
	return std::make_unique<CallPayoff>(*this);
}

PutPayoff::PutPayoff(double strike): strike_{strike} {}

double PutPayoff::payoff(double spot) const
{
	return std::max(strike_ - spot, 0.0);
}

std::unique_ptr<Payoff> PutPayoff::clone() const
{
	return std::make_unique<PutPayoff>(*this);
}