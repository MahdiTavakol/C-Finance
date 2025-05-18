#include "ExampleDeclarations.h"
#include "DayCounts.h"
#include <iostream>
#include <iomanip>
#include <format>

using std::cout;
using std::format;

void day_count_basis_tests()
{
	book_examples();
	treasury_bill_examples();
}

void book_examples()
{
	cout << "\n" << "*** book_examples() ***\n";

	Act365 act_365{};
	Act360 act_360{};
	Thirty360 thirty_360{};

	ChronoDate sd_01{ 2021,4,26 }; 
	ChronoDate ed_01{ 2023,10,26 };
	ChronoDate sd_02{ 2022,10,10 };
	ChronoDate ed_02{ 2023,4,10 };

	double yf_act_365_01 = act_365.year_fraction( sd_01,ed_01 );
	double yf_act_365_02 = act_365.year_fraction( sd_02,ed_02 );

	double yf_act_360_01 = act_360.year_fraction( sd_01,ed_01 );
	double yf_act_360_02 = act_360.year_fraction( sd_02, ed_02);

	double yf_thirty_01 = thirty_360.year_fraction(sd_01, ed_01);
	double yf_thirty_02 = thirty_360.year_fraction(sd_02, ed_02);

	cout << "Year fraction (Act/365) between " << sd_01 << " & " << ed_01 << " = " << yf_act_365_01 << "\n";
	cout << "Year fraction (Act/360) between " << sd_02 << " & " << ed_02 << " = " << yf_act_365_02 << "\n\n";

	cout << "Year fraction (Act/365) between " << sd_01 << " & " << ed_01 << " = " << yf_act_360_01 << "\n";
	cout << "Year fraction (Act/360) between " << sd_02 << " & " << ed_02 << " = " << yf_act_360_02 << "\n\n";

	cout << "Time (in years) (Act/365) between " << sd_01 << " & " << ed_01 << " = " << yf_thirty_01 << "\n";
	cout << "Time (in years) (Act/360) between " << sd_02 << " & " << ed_02 << " = " << yf_thirty_02 << "\n\n";

}

double treasury_bill(const ChronoDate& sett_date,
	const ChronoDate& maturity_date, double mkt_yield,
	double face_value, const DayCount& dc)
{
	return face_value / (1.0 * mkt_yield * dc.year_fraction(sett_date, maturity_date));
}

void treasury_bill_example()
{
	cout << "\n" << "*** treasury_bill_example() (DayCountBasisTest.cpp) ***\n";
	double us_face = 20000;
	double uk_face = 15000;
	double us_yield = 0.045;
	double uk_yield = 0.036;
	ChronoDate sett_date{ 2023,5,8 };
	ChronoDate maturity_date{ 2023,7,15 };

	double us_val = treasury_bill(sett_date, maturity_date, us_yield, us_face, Act365{});
	double uk_val = treasury_bill(sett_date, maturity_date, uk_yield, uk_face, Act360{});

	cout << std::fixed << std::setprecision(2);
	cout << "US Treas Bill price = " << us_val << "\n";
	cout << "UK Treas Bill price = " << uk_val << "\n\n";
}