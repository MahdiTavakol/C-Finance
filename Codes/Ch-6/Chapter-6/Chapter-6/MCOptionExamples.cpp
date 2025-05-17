#include "ExampleDeclarations.h"
#include "Payoffs.h"
#include "MCOptionValuation.h"

#include <random>
#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>
#include <format>

void mc_option_examples()
{
	euro_no_barrier_examples();
	euro_with_barrier_examples();
}

void euro_no_barrier_examples()
{
	using std::cout, std::format;
	cout << "\n*** euro_no_barrier_examples() ***\n";

	double strike = 75.0;
	double spot = 100.0;
	double vol = 0.25;
	double rate = 0.05;
	double div = 0.075;
	double time_to_exp = 0.5;
	int num_time_steps = 12;
	int num_scenarios = 20000;
	unsigned seed = 42;

	cout << format("ITM call option with time to exp = {}, dividend rate = {}\n", time_to_exp, div);
	// std::make_unique itself creates a rhs so there is no need for std::move here!
	OptionInfo opt_call_itm{ std::move(std::make_unique<CallPayoff>(strike)),time_to_exp };
	MCOptionValuation val_call_itm{ std::move(opt_call_itm),num_time_steps,vol,rate,div };

	double opt_value = val_call_itm.calc_price(spot, num_scenarios, seed);

	cout << std::fixed << std::setprecision(2) << "ITM call option price = " << opt_value << "\n";

	cout << "\n\n";
}

void euro_with_barrier_examples()
{
	using std::cout, std::format;
	cout << "\n" << "*** euro_with_barrier_examples() ***\n";

	double strike = 75.0;
	double spot = 100.0;
	double vol = 0.25;
	double rate = 0.05;
	double div = 0.075;
	double time_to_exp = 0.5;
	int num_time_steps = 12;
	int num_scenarios = 20000;
	unsigned seed = 42;

	BarrierType barr_type = BarrierType::up_and_out;
	double barr_val = 110.0;

	cout << format("ITM Call option with time value = {}, dividend rate = {}, up/out barr_val = {}:\n",
		time_to_exp, div, barr_val);

	OptionInfo opt_call_itm_barr{ std::make_unique<CallPayoff>(strike),time_to_exp };
	MCOptionValuation val_call_itm_barr{ std::move(opt_call_itm_barr),
	num_time_steps, vol,rate, div, barr_type, barr_val };

	cout << "Option Value = " << val_call_itm_barr.calc_price(spot, seed, num_scenarios) << "\n\n";

	num_time_steps = 2400;
	num_scenarios = 50000;

	OptionInfo opt_call_itm_barr_2{ std::make_unique<CallPayoff>(strike),time_to_exp };
	MCOptionValuation val_call_itm_barr_2{ std::move(opt_call_itm_barr_2),
	num_time_steps,vol,rate,div,barr_type,barr_val };

	cout << "Option Value = " << val_call_itm_barr_2.calc_price(spot, num_scenarios, seed) << "\n\n";
	cout << "Analytic soluton price = 5.61" << "\n\n";

	strike = 105.0;
	spot = 100.0;
	vol = 0.25;
	rate = 0.05;
	div = 0.08;
	seed = 42;

	barr_type = BarrierType::down_and_out;
	barr_val = 70.5;

	time_to_exp = 1.0;
	num_time_steps = 24;
	num_scenarios = 20000;

	cout << format("ITM Put option with time value = {}, dividend rate = {}, up/out barr_val = {}\n",
		time_to_exp,div, barr_val);

	OptionInfo vo_put_itm_no_exp{ std::make_unique<PutPayoff>(strike),time_to_exp };
	MCOptionValuation val_put_itm_no_exp{ std::move(vo_put_itm_no_exp),num_time_steps,
	vol,rate,div,barr_type, barr_val };

	double opt_val = val_put_itm_no_exp.calc_price(spot, num_scenarios, seed);
	cout << std::fixed << std::setprecision(2) << "Option Value= " << opt_val << "\n\n";

	num_time_steps = 4800;
	num_scenarios = 50000;

	OptionInfo vo_put_itm_no_exp_2{ std::make_unique<PutPayoff>(strike),time_to_exp };
	MCOptionValuation val_put_itm_no_exp_2{ std::move(vo_put_itm_no_exp_2),num_time_steps,vol,
	rate,div,barr_type,barr_val };

	opt_val = val_put_itm_no_exp_2.calc_price(spot, num_scenarios, seed);
	cout << std::fixed << std::setprecision(2) << "Option Value= " << opt_val << "\n\n";

	cout << "Analytic solution price = 6.29" << "\n\n";
}