#include "MCOptionValuation.h"
#include "EquityPriceGenerator.h"

#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <random>
#include <future>

// This is the form of the constructor for the European option
// example as shown at the outset of the section in the Chapter.
// It was generalized to include knockout barriers in the 
// (non-commented out) constructor that follows after.
/*
MCOptionValuation::MCOptionValuation(OptionInfo&& opt, int time_steps, double vol,
	double int_rate, double div_rate) : opt_{std::move(opt)}, time_steps_{time_steps},
	vol_{vol}, int_rate_{int_rate}, div_rate_{div_rate} {}
*/

MCOptionValuation::MCOptionValuation(OptionInfo&& opt, int time_steps, double vol,
	double int_rate, double div_rate, BarrierType barrier_type, double barrier_value) : opt_{ std::move(opt) }, time_steps_{ time_steps },
	vol_{ vol }, int_rate_{ int_rate }, div_rate_{ div_rate },
	barrier_type_{ barrier_type }, barrier_value_{barrier_value} {}


double MCOptionValuation::calc_price_euro(double spot, int num_scenarios, unsigned unif_start_seed)
{
	if (opt_.time_to_expiration() > 0.0)
	{
		using std::vector;

		std::mt19937_64 mt_unif{ unif_start_seed };
		std::uniform_int_distribution<unsigned> unif_int_dist{};
		

		vector<double> discounted_payoffs;
		discounted_payoffs.reserve(num_scenarios);
		const double disc_factor = std::exp(-int_rate_ * opt_.time_to_expiration());

		for (int i = 0; i < num_scenarios; i++)
		{
			EquityPriceGenerator epg{ spot, time_steps_, opt_.time_to_expiration(),vol_,
			int_rate_, div_rate_ };
			vector scenario = epg(unif_int_dist(mt_unif));

			discounted_payoffs.push_back(disc_factor *
				opt_.option_payoff(scenario.back()));
		}

		return (1.0 / num_scenarios) *
			std::accumulate(discounted_payoffs.cbegin(), discounted_payoffs.cend(), 0.0);
	}
	else
	{
		return opt_.option_payoff(spot);
	}
}

double MCOptionValuation::calc_price(double spot, int num_scenarios, unsigned unif_start_seed)
{
	bool barrier_hit =
		(barrier_type_ == BarrierType::up_and_out && spot >= barrier_value_) ||
		(barrier_type_ == BarrierType::down_and_out && spot <= barrier_value_);

	if (barrier_hit) return 0.0;

	if (opt_.time_to_expiration() > 0)
	{
		std::mt19937_64 mt_unif{ unif_start_seed };
		std::uniform_int_distribution<unsigned> unif_int_dist{};
		const double disc_factor = std::exp(-int_rate_ * opt_.time_to_expiration());

		using std::vector;
		vector<double> discounted_payoffs;
		discounted_payoffs.reserve(num_scenarios);

		for (int i = 0; i < num_scenarios; ++i)
		{
			EquityPriceGenerator epg{ spot, time_steps_, opt_.time_to_expiration(), vol_,
				int_rate_, div_rate_ };
			vector scenario = epg(unif_int_dist(mt_unif));

			switch (barrier_type_)
			{
			case BarrierType::none:
				break;

			case BarrierType::up_and_out:
			{
				auto barrier_hit_pos = std::find_if(scenario.cbegin(), scenario.cend(),
					[this](double sim_eq) {return sim_eq >= barrier_value_; });

				if (barrier_hit_pos != scenario.cend()) barrier_hit = true;
			}
			break;

			case BarrierType::down_and_out:
			{
				auto barrier_hit_pos = std::ranges::find_if(scenario,
					[this](double sim_eq) {return sim_eq <= barrier_value_; });
				if (barrier_hit_pos != scenario.cend()) barrier_hit = true;
			}
			break;
			}

			if (barrier_hit)
			{
				discounted_payoffs.push_back(0.0);
			}
			else
			{
				discounted_payoffs.push_back(disc_factor *
					opt_.option_payoff(scenario.back()));
			}

			barrier_hit = false;

		}

		return (1.0 / num_scenarios) *
			std::accumulate(discounted_payoffs.cbegin(), discounted_payoffs.cend(), 0.0);
	}

	else
	{
		return opt_.option_payoff(spot);
	}
}

double MCOptionValuation::calc_price_par(double spot, int num_scenarios, unsigned unif_start_seed)
{
	bool barrier_hit =
		(barrier_type_ == BarrierType::up_and_out && spot >= barrier_value_) ||
		(barrier_type_ == BarrierType::down_and_out && spot <= barrier_value_);

	if (barrier_hit) return 0.0;

	double opt_val = 0.0;
	if (opt_.time_to_expiration() > 0)
	{
		using std::vector;

		std::mt19937_64 mt_unif{ unif_start_seed };
		std::uniform_int_distribution<unsigned> unif_int_dist{};

		vector<double> discounted_payoffs;
		discounted_payoffs.reserve(num_scenarios);
		const double disc_factor = std::exp(-int_rate_ * opt_.time_to_expiration());

		vector<std::future<double>> ftrs;
		ftrs.reserve(num_scenarios);

		if (barrier_hit != true)
		{
			for (int i = 0; i < num_scenarios; i++)
			{
				EquityPriceGenerator epg{ spot,time_steps_,opt_.time_to_expiration(),vol_,
				int_rate_,div_rate };

				ftrs.push_back(std::async(epg, unif_int_dist(mt_unif)));

			}

			for (auto& ftr : ftrs)
			{
				vector scenario = ftr.get();

				switch (barrier_type_)
				{
					case BarrierType::none:
						break;
					case BarrierType::up_and_out:
					{
						auto barrier_hit_pos = std::find_if(scenario.cbegin(), scenario.cend(),
							[this](double sim_eq) {return sim_eq >= barrier_value_; });
						if (barrier_hit_pos != scenario.cend()) barrier_hit = true;
					}
					break;
					case BarrierType::down_and_out:
					{
						auto barrier_hit_pos = std::ranges::find_if(scenario,
							[this](double sim_eq) {return sim_eq <= barrier_value_; });
						if (barrier_hit_pos != scenario.cend()) barrier_hit = true;
					}
					break;
				}

				if (barrier_hit)
				{
					discounted_payoffs.push_back(0.0);
				}
				else
				{
					discounted_payoffs.push_back(disc_factor * opt_.option_payoff(scenario.back()));
				}

				barrier_hit = false;
			}
		}

		return (1.0 / num_scenarios) * std::accumulate(discounted_payoffs.cbegin(),
			discounted_payoffs.cend(), 0.0);
	}
	else
	{
		return opt_.option_payoff(spot);
	}
}