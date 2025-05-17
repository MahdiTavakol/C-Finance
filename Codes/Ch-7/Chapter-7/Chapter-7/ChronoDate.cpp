#include "ChronoDate.h"
#include <stdexcept>
#include <utility>

ChronoDate::ChronoDate(int year, unsigned month, unsigned day)
	: date_{ std::chrono::year{ year }, std::chrono::month{ month }, std::chrono::day{ day } }
{
	validate_();
}

ChronoDate::ChronoDate(std::chrono::year_month_day ymd) :
	date_{ std::move(ymd) }
{
	validate_();
}

void ChronoDate::validate_() const
{
	if (!date_.ok())
	{
		throw std::invalid_argument{ "ChronoDate constructor: invalid date." };
	}
}

int ChronoDate::serial_date() const
{
	return std::chrono::sys_days(date_).time_since_epoch().count();
}

std::chrono::year_month_day ChronoDate::ymd() const
{
	return date_;
}

int ChronoDate::year() const
{
	return static_cast<int>(date_.year());
}

unsigned ChronoDate::month() const
{
	return static_cast<unsigned>(date_.month());
}

unsigned ChronoDate::day() const
{
	return static_cast<unsigned>(date_.day());
}

unsigned ChronoDate::days_in_month() const
{
	using namespace std::chrono;
	year_month_day_last eom{ date_.year() / date_.month() / last };
	return static_cast<unsigned>(eom.day());
}

bool ChronoDate::is_end_of_month() const
{
	return date_ == date_.year() / date_.month() / std::chrono::last;
}

bool ChronoDate::is_leap_year() const
{
	return date_.year().is_leap();
}

int ChronoDate::operator - (const ChronoDate& rhs) const
{
	return this->serial_date() - rhs.serial_date();
}

bool ChronoDate::operator == (const ChronoDate& rhs) const
{
	return this->serial_date() == rhs.serial_date();
}

std::strong_ordering ChronoDate::operator <=> (const ChronoDate& rhs) const
{
	if (this->serial_date() < rhs.serial_date())
	{
		return std::strong_ordering::less;
	}
	else if (this->serial_date() > rhs.serial_date())
	{
		return std::strong_ordering::greater;
	}
	else
	{
		return std::strong_ordering::equal;
	}
}

ChronoDate& ChronoDate::add_years(int rhs_years)
{
	date_ += std::chrono::years(rhs_years);

	if (!date_.ok())
	{
		date_ = date_.year() / date_.month() / 28;
	}

	return *this;
}

ChronoDate& ChronoDate::add_months(int rhs_months)
{
	date_ += std::chrono::months(rhs_months);

	if (!date_.ok())
	{
		date_ = date_.year() / date_.month() / std::chrono::day{ days_in_month() };
	}

	return *this;
}

ChronoDate& ChronoDate::add_days(int rhs_days)
{
	using namespace std::chrono;

	date_ = sys_days(date_) + days{ rhs_days };
}

ChronoDate& ChronoDate::weekend_roll()
{
	using namespace std::chrono;

	weekday wd{ sys_days(date_) };
	std::chrono::month orig_mth{ date_.month() };

	unsigned wdn{ wd.iso_encoding() };

	if (wdn > 5) date_ = sys_days(date_) + days(8 - wdn);

	if (orig_mth != date_.month())
	{
		date_ = sys_days(date_) - days(3);
	}

	return *this;
}

std::ostream& operator << (std::ostream& os, const ChronoDate& rhs)
{
	os << rhs.ymd();
	return os;
}