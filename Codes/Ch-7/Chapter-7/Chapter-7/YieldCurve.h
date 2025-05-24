#pragma once

#include "ChronoDate.h"
#include "DayCounts.h"

class YieldCurve
{
public:
	double discount_factor(const ChronoDate& date_01, const ChronoDate& date_02) const;
	virtual ~YieldCurve() = default;

	ChronoDate settle_date() const;

protected:
	YieldCurve(ChronoDate settle_date);
	Act365 act_365() const;

private:
	virtual double yield_curve_(double t) const = 0;

	ChronoDate settle_;
	inline static Act365 act_365_{};
};

class LinearInterpYieldCurve : public YieldCurve
{
public:
	LinearInterpYieldCurve(const ChronoDate& settle_date,
		const std::vector<ChronoDate>& maturity_dates,
		const std::vector<double>& unit_prices);

private:
	double yield_curve_(double t) const override;

	std::vector<double> maturities_;
	std::vector<double> yields_;
};
