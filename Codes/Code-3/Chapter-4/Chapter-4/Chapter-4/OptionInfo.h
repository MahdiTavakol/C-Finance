#pragma once

#include "Payoffs.h"
#include <memory>



// In what follows, OptionInfo demonstrates how to implement RAII in a 
// modern (C++11/C++14) manner, using a unique pointer member, instead 
// of a raw pointer and "virtual constructor" as seen in the C++03 version above.

class OptionInfo
{
public:
	OptionInfo(std::unique_ptr<Payoff> payoff, double time_to_exp);
	double option_payoff(double spot) const;
	double time_to_expiration() const;
	void swap(OptionInfo& rhs) noexcept;

	OptionInfo(const OptionInfo& rhs);
	OptionInfo& operator =(const OptionInfo& rhs) noexcept;

	// Remaining Rule of Five:
	OptionInfo(OptionInfo&& rhs) = default;					// Default move constructor
	OptionInfo& operator =(OptionInfo&& rhs) = default;		// Default move assignment

	~OptionInfo() = default;										// Default destructor

private:
	std::unique_ptr<Payoff> payoff_ptr_;
	double time_to_exp_;
};


/*
	A portion of this sample code is derived from sample code provided on CD
	to accompany the book _C++ Design Patterns and Derivatives Pricing (2E)_,
	by Mark Joshi, 2008.

	Its accompanying license agreement is as follows:

	The code is released under an artistic license. This means that you
	can do what you like with it, provided that if you redistribute the
	source code you allow the receiver to do what they like with it too.

	Otherwise, this sample code is Copyright 2023, Daniel Hanson, and
	released under the BSD-3 license.
*/

void cpp11_examples();