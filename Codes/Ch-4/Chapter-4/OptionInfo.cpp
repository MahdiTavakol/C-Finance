#include "OptionInfo.h"
#include <utility>		// std::move, std::swap
#include <stdexcept>
#include <iostream>
#include <format>

#include <string>

// In what follows, OptionInfo demonstrates how to implement RAII in a 
// modern (C++11/C++14) manner, using a unique pointer member, instead 
// of a raw pointer and "virtual constructor" as seen in the C++03 version above.

OptionInfo::OptionInfo(std::unique_ptr<Payoff> payoff, double time_to_exp) :
	payoff_ptr_{ std::move(payoff) }, time_to_exp_{ time_to_exp } {}

double OptionInfo::option_payoff(double spot) const
{
	return payoff_ptr_->payoff(spot);
}

double OptionInfo::time_to_expiration() const
{
	return time_to_exp_;
}

void OptionInfo::swap(OptionInfo& rhs) noexcept
{
	using std::swap;
	swap(payoff_ptr_, rhs.payoff_ptr_);
	swap(time_to_exp_, rhs.time_to_exp_);
	//throw std::runtime_error{"Error:..."};	// Compiler warning, runtime error (for demonstration)
}

// Copy Constructor:
OptionInfo::OptionInfo(const OptionInfo& rhs) :
	payoff_ptr_{ rhs.payoff_ptr_->clone() },
	time_to_exp_{ rhs.time_to_expiration() } {}

// Copy Assignment:
OptionInfo& OptionInfo::operator =(const OptionInfo& rhs) noexcept
{
	OptionInfo{ rhs }.swap(*this);
	return *this;
}



void option_info_examples()
{
	cpp11_examples();
}



void cpp11_examples()
{
	using std::cout;
	using std::format;

	cout << "\n" << "*** cpp11_examples() (RAII) ***" << "\n";

	auto call_payoff = std::make_unique<CallPayoff>(75.0);
	OptionInfo call_opt{ std::move(call_payoff), 0.5 };

	// Alternatively, this could be written in one line with an anonymous temporary unique pointer:
	//OptionInfo call_opt{std::make_unique<CallPayoff>(75.0), 0.5};

	cout << "\n" << format("Payoff for call option with {} year(s) to expiration = {}",
		call_opt.time_to_expiration(), call_opt.option_payoff(85.0)) << "\n";

	// Need copy operations implemented on OptionInfo to construct
	// call_copy and call_copy_assgn; otherwise, comment out the following `#if 0` block.
//#if 0
	OptionInfo call_copy{ call_opt };		// Need copy operations implemented on OptionInfo
	cout << "\n" << format("Payoff for _copied_ call option with {} year(s) to expiration = {}",
		call_copy.time_to_expiration(), call_copy.option_payoff(90.0)) << "\n";

	OptionInfo call_copy_assgn{ call_copy };
	call_copy_assgn = call_opt;
	//#endif

		// Moves, however, are provided by default (but be sure to heed the
		// Rule of Zero or Rule of Five):
	OptionInfo call_move{ std::move(call_opt) };
	cout << "\n" << format("Payoff for _moved_ (ctor) call option with {} year(s) to expiration = {}",
		call_move.time_to_expiration(), call_move.option_payoff(100.0)) << "\n";

	OptionInfo call_move_assgn{ std::make_unique<CallPayoff>(75.0), 0.5 };
	call_move_assgn = std::move(call_move);
	cout << "\n" << format("Payoff for _moved_ (=) call option with {} year(s) to expiration = {}",
		call_move_assgn.time_to_expiration(), call_move_assgn.option_payoff(100.0)) << "\n\n";
}

/*
	A portion of this sample code (C++03 example of RAII) is based on sample code
	provided on CD to accompany the book _C++ Design Patterns and Derivatives Pricing (2E)_,
	by Mark Joshi, 2008.

	Its accompanying license agreement is as follows:

	The code is released under an artistic license. This means that you
	can do what you like with it, provided that if you redistribute the
	source code you allow the receiver to do what they like with it too.

	Otherwise, this sample code is Copyright 2023, Daniel Hanson, and
	released under the BSD-3 license.
*/


