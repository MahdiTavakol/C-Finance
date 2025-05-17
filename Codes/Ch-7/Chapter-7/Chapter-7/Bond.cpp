
#include "Bond.h"
#include <iterator>

Bond::Bond(const std::string& bond_id, const ChronoDate& dated_date,
	const ChronoDate& first_coupon_date, const ChronoDate& penultimate_coupon_date,
	const ChronoDate& maturity_date, int coupon_frequency, double coupon_rate,
	double face_value) : bond_id_{ bond_id }
{
	const int months_in_regular_coupon_period = 12 / coupon_frequency;
	const double regular_coupon_payment = coupon_rate * face_value / coupon_frequency;

	calculate_pmt_schedule_(first_coupon_date, penultimate_coupon_date,
		months_in_regular_coupon_period, regular_coupon_payment);
	amend_initial_irregular_dates_and_pmts_(dated_date, first_coupon_date,
		months_in_regular_coupon_period, regular_coupon_payment);
	amend_final_irregular_dates_and_pmts_(penultimate_coupon_date, maturity_date,
		months_in_regular_coupon_period, regular_coupon_payment);

	due_dates_.push_back(maturity_date);
	payment_dates_.push_back(maturity_date);
}

void Bond::calculate_pmt_schedule_(const ChronoDate& first_coupon_date,
	const ChronoDate& penultimate_coupon_date, const int months_in_regular_coupon_period,
	const double regular_coupon_payment)
{
	for (ChronoDate regular_due_date{ first_coupon_date };
		regular_due_date <= penultimate_coupon_date;
		regular_due_date.add_months(months_in_regular_coupon_period))
	{
		due_dates_.push_back(regular_due_date);
		ChronoDate payment_date{ regular_due_date };

		payment_dates_.push_back(payment_date.weekend_roll());
		payment_amounts_.push_back(regular_coupon_payment);
	}
}

void Bond::amend_initial_irregular_dates_and_pmts_(const ChronoDate& dated_date,
	const ChronoDate& first_coupon_date, const int months_in_regular_coupon_period,
	const double regular_coupon_payment)
{
	ChronoDate first_prior{ first_coupon_date };
	first_prior.add_months(-months_in_regular_coupon_period);
	if (first_prior != dated_date)
	{
		if (first_prior < dated_date)
		{
			double coupon_fraction =
				static_cast<double>(first_coupon_date - dated_date) /
				static_cast<double>(first_coupon_date - first_prior);

			payment_amounts_[0] *= coupon_fraction;
		}
		else
		{
			ChronoDate second_prior{ first_prior };
			second_prior.add_months(-months_in_regular_coupon_period);
			double coupon_fraction = static_cast<double>(first_prior - dated_date) /
				static_cast<double>(first_prior - second_prior);
			payment_amounts_[0] += coupon_fraction * regular_coupon_payment;
		}
	}
}

void Bond::amend_final_irregular_dates_and_pmts_(const ChronoDate& penultimate_coupon_date,
	const ChronoDate& maturity_date, const int months_in_regular_coupon_period,
	const double regular_coupon_payment, const double face_value)
{
	ChronoDate maturity_regular_date{ penultimate_coupon_date };
	maturity_regular_date.add_months(months_in_regular_coupon_period);
	double final_coupon{ regular_coupon_payment };

	if (maturity_regular_date != maturity_date)
	{
		if (maturity_date < maturity_regular_date)
		{
			double coupon_fraction =
				static_cast<double>(maturity_date - penultimate_coupon_date) /
				static_cast<doublE>(maturity_regular_date - penultimate_coupon_date);
			final_coupon *= coupon_fraction;
		}
		else
		{
			ChronoDate next_regular_date{ maturity_regular_date };
			next_regular_date.add_months(months_in_regular_coupon_period);
			double extra_coupon_fraction =
				static_cast<double>(maturity_date - maturity_regular_date) /
				static_cast<double>(next_regular_date - maturity_regular_date);
			final_coupon += extra_coupon_fraction * regular_coupon_payment;
		}
	}
	payment_amounts_.push_back(final_coupon + face_value);
}

double Bond::discounted_value(const ChronoDate& bond_settle_date, const YieldCurve& yield_curve)
{
	double pv = 0.0;
	for (size_t i = 0; i < due_dates.size(); i++)
	{
		if (bond_settle_date < due_dates_[i])
		{
			pv += yield_curve.discount_factor(bond_settle_date, payment_dates_[i]) * payment_amounts_[i];
		}
	}
	return yield_curve.discount_factor(yield_curve.settle_date(), bond_settle_date) * pv;
}

std::string Bond::bond_id() const
{
	return bond_id_;
}


