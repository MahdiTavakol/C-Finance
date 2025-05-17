
#include "DayCounts.h"
#include <utility>

double Act365::year_fraction(const ChronoDate& date_01, const ChronoDate& date_02) const
{
	return (date_02 - date_01) / 365.0;
}

double Act360::year_fraction(const ChronoDate& date_01, const ChronoDate& date_02) const
{
	return (date_02 - date_01) / 360.0;
}

double Thirty360::year_fraction(const ChronoDate& date_01, const ChronoDate& date_02) const
{
	return date_diff_(date_01, date_02) /360.0;
}

int Thirty360::date_diff_(const ChronoDate& date_01, const ChronoDate& date_02) const
{
	int d1, d2;
	d1 = date_01.day();
	d2 = date_02.day();

	if (d1 == 31) d1 = 30;

	if ((d2 == 31) && (d1 == 30)) d2 = 30;

	return 360 * (date_02.year() - date_01.year()) + 30 * (date_02.month() - date_01.month()) + d2 - d1;
}
