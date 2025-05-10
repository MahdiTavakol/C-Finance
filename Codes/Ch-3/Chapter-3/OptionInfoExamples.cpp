#include "Ch03_example_functions.h"
#include "OptionInfo.h"
#include <utility>
#include <stdexcept>
#include <iostream>
#include <format>

#include <string>

void option_info_examples()
{
	cpp03_examples();
	cpp11_examples();
}

void cpp03_examples()
{
	using std::cout;
	using std::format;

	cout << "\n" << "*** cpp03_examples() (RAII) ***" << "\n";

	Payoff03* call_payoff = new CallPayoff03(75.0);
	OptionInfo03 call_opt(call_payoff, 0.5);

	cout << "\n" << format("Payoff for call option with {} year(s) to expiration = {}", 
		call_opt.time_to_expiration(), call_opt.option_payoff(85.0)) << "\n";

	// both of these will call the copy constructor despite the assignment sign!
	OptionInfo03 copy{ call_opt };
	OptionInfo03 copy_assgn = call_opt;

	cout << "\n" << format("Payoff for call option (copy ctor) with {} year(s) to expiration = {}",
		copy.time_to_expiration(), copy.option_payoff(95.0));

	cout << "\n" << format("Payoff for call option (copy assgn) with {} year(s) to expiration = {}",
		copy_assgn.time_to_expiration(), copy_assgn.option_payoff(95.0));
}

void cpp11_examples()
{
	using std::cout;
	using std::format;

	cout << "\n" << "*** cpp11_examples() (RAII) ***" << "\n";

	auto call_payoff = std::make_unique<CallPayoff>(75.0);
	//std::unique_ptr<Payoff> call_payoff = std::make_unique<CallPayoff>(75.0);
	OptionInfo call_opt{ std::move(call_payoff),0.5 };

	cout << "\n" << format("Payoff for call option with {} year(s) to expiration = {}",
		call_opt.time_to_expiration(), call_opt.option_payoff(85.0)) << "\n";

	OptionInfo call_copy{ call_opt };
	cout << "\n" << format("Payoff for _copied_ call option with {} year(s) to expirate = {}",
		call_copy.time_to_expiration(), call_copy.option_payoff(90.0)) << "\n";

	OptionInfo call_copy_assgn{ call_copy };
	call_copy_assgn = call_opt;

	OptionInfo call_move{ std::move(call_opt) };
	cout << "\n" << format("Payoff for _moved_ (ctor) call option with {} year(s) to expiration = {}",
		call_move.time_to_expiration(), call_move.option_payoff(100.0)) << "\n";

	OptionInfo call_move_assgn{ std::make_unique<CallPayoff>(75.0),0.5 };
	call_move_assgn = std::move(call_move);
	cout << "\n" << format("Payoff for _moved_ (=) call option with {} year(s) to expiration = {}",
		call_move_assgn.time_to_expiration(), call_move_assgn.option_payoff(100.0)) << "\n\n";


 }