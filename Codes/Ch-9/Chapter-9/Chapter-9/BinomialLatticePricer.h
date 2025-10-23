#pragma once

#include <boost/multi_array.hpp>
#include "OptionInfo.h"

enum class OptType
{
	Euro,
	American
};

enum class KnockoutType
{
	None,
	Up,
	Down
};

struct Node
{
	double underlying;
	double payoff;
};

class BinomialLatticePricer
{
public:

	BinomialLatticePricer(OptionInfo opt_,
		double vol_, double int_rate_, int time_points_,
		double div_rate_ = 0.0);

	double calc_price(double spot_, OptType opt_type);

	void display_lattice_nodes() const;

private:
	OptionInfo opt;
	int time_points;
	double div_rate;

	double u{ 0.0 }, d{ 0.0 }, p{ 0.0 };
	double disc_fctr;

	boost::multi_array<Node, 2> grid;

	void project_underlying_prices(double spot_);
	double calculate_node_payoffs(OptType opt_type_);

	double disc_expected_val(int i, int j) const;
	void american_payoffs();
	void european_payoffs();
};
