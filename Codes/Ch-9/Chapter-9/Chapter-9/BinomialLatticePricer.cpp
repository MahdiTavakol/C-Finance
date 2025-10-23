#include "BinomialLatticePricer.h"

#include <algorithm>
#include <limits>
#include <utility>

#include <iostream>
#include <iomanip>

BinomialLatticePricer::BinomialLatticePricer(OptionInfo opt_,
	double vol_, double int_rate_, int time_steps_, double div_rate_) :
	opt{ std::move(opt_) }, time_points{ time_steps_ + 1 }, div_rate{ div_rate_ }
{
	double dt{ opt.time_to_expiration() / time_steps_ };
	u = std::exp(vol_ * std::sqrt(dt));
	d = 1.0 / u;
	p = 0.5 * (1.0 + (int_rate_ - div_rate - 0.5 * vol_ * vol_) * std::sqrt(dt) / vol_);
	disc_fctr = std::exp((-int_rate_ * dt));

	grid.resize(boost::extents[time_points][time_points]);

}

double BinomialLatticePricer::calc_price(double spot_, OptType opt_type_)
{
	project_underlying_prices(spot_);
	return calculate_node_payoffs(opt_type_);
}

void BinomialLatticePricer::project_underlying_prices(double spot_)
{
	grid[0][0].underlying = spot_;

	for (int j = 1; j < time_points; ++j)
	{
		for (int i = 0; i <= j; i++)
		{
			if (i < j)
			{
				grid[i][j].underlying = u * grid[i][j - 1].underlying;
			} 
			else
			{
				grid[i][j].underlying = d * grid[i - 1][j - 1].underlying;
			}
		}
	}
}

double BinomialLatticePricer::calculate_node_payoffs(OptType opt_type_)
{
	for (int i = 0; i <= time_points - 1; i++)
	{
		grid[i][time_points - 1].payoff =
			opt.option_payoff(grid[i][time_points - 1].underlying);
	}

	if (opt_type_ == OptType::American)
		american_payoffs();
	else
		european_payoffs();

	return grid[0][0].payoff;

}

double BinomialLatticePricer::disc_expected_val(int i, int j) const
{
	return disc_fctr * (p * grid[i][j + 1].payoff +
		(1.0-p)*grid[i+1][j+1].payoff);
}

void BinomialLatticePricer::american_payoffs()
{
	for (int j = time_points - 2; j >= 0; --j)
	{
		for (int i = 0; i <= j; ++i)
		{
			grid[i][j].payoff = std::max(disc_expected_val(i, j),
				opt.option_payoff(grid[i][j].underlying));
		}
	}
}

void BinomialLatticePricer::european_payoffs()
{
	for (int j = time_points - 2; j >= 0; --j)
	{
		for (int i = 0; i <= j; ++i)
		{
			auto expo = disc_expected_val(i, j);
			grid[i][j].payoff = disc_expected_val(i, j);
		}
	}
}

void BinomialLatticePricer::display_lattice_nodes() const
{
	using std::cout;

	for (int i = 0; i < time_points; ++i)
	{
		for (int k = 0; k < i; ++k)
			cout << "\t";
		for (int j = i; j < time_points; ++j)
		{
			cout << std::fixed << std::setprecision(2) << grid[i][j].underlying;
			cout << "\t";
		}
		cout << "\n";
	}
	cout << "\n\n";

	for (int i = 0; i < time_points; i++)
	{
		for (int k = 0; k < i; ++k)
			cout << "\t";
		for (int j = 0; j < time_points; ++j)
		{
			auto the_payoff = grid[i][j].payoff > 10e-10 ? grid[i][j].payoff : 0.0;
			cout << std::fixed << std::setprecision(2) << the_payoff;
			cout << "\t";
		}
		cout << "\n";
	}
	cout << "\n\n";
}