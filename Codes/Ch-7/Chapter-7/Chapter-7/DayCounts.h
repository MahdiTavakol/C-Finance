#pragma once

#include "ChronoDate.h"

class DayCount
{
public:
	virtual double year_fraction(const ChronoDate& date_01, const ChronoDate& date_02) const = 0;
	virtual ~DayCount() = default;
};

class Act365 : public DayCount
{
public:
	double year_fraction(const ChronoDate& date_01, const ChronoDate& date_02) const override;
};

class Act360 : public DayCount
{
public:
	double year_fraction(const ChronoDate& date_01, const ChronoDate& date_02) const override;
};

class Thirty360 : public DayCount
{
public:
	double year_fraction(const ChronoDate& date_01, const ChronoDate& date_02) const override;
private:
	int date_diff_(const ChronoDate& date_01, const ChronoDate& date_02) const;
};

