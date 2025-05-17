#pragma once

#include <chrono>
#include <compare>

class ChronoDate
{
public:
	ChronoDate(int year, unsigned month, unsigned day);

	ChronoDate(std::chrono::year_month_day ymd);
	ChronoDate() = default;

	int serial_date() const;
	std::chrono::year_month_day ymd() const;
	int year() const;
	unsigned month() const;
	unsigned day() const;

	unsigned days_in_month() const;
	bool is_end_of_month() const;
	bool is_leap_year() const;

	int operator - (const ChronoDate& other) const;
	bool operator == (const ChronoDate& other) const;
	std::strong_ordering operator <=> (const ChronoDate& other) const;

	ChronoDate& add_years(int rhs_years);
	ChronoDate& add_months(int rhs_months);
	ChronoDate& add_days(int rhs_days);
	ChronoDate& weekend_roll();

private:
	std::chrono::year_month_day date_
	{ std::chrono::year{1970},std::chrono::month{1},std::chrono::day{1} };

	void validate_() const;


};

std::ostream& operator << (std::ostream& os, const ChronoDate& rhs);