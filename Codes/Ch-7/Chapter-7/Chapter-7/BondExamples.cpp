#include "ExampleDeclarations.h"
#include "ChronoDate.h"
#include "Bond.h"
#include "YieldCurve.h"
#include "DayCounts.h"

#include <vector>
#include <memory>
#include <utility>
#include <string>
#include <format>
#include <iostream>
#include <iomanip>

namespace date = std::chrono;
using std::exp;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::string;
using std::format;
using std::cout, std::endl;

void dow(const ChronoDate& rhs)
{
	date::weekday dw{ rhs.ymd() };
	cout << rhs.ymd() << ", " << dw << endl;
}

void valuation_20_yr_bond()
{
	cout << "\n" << "*** valuation_20_yr_bond() ***\n";

	string bond_id = "20 yr bond";
	ChronoDate dated_date{ 2023,5,8 };
	ChronoDate first_coupon_date{ 2023,11,7 };
	ChronoDate penultimate_coupon_date{ 2042,11,7 };
	ChronoDate maturity_date{ 2043,5,7 };

	const int coupon_frequency = 2;
	const double coupon_rate = 0.062;
	const double face_value = 1000.0;


	// Summarize:
	cout << "Dated Date: ";
	dow(dated_date);
	cout << "\n" << "1st Coupon Date: ";
	dow(first_coupon_date);
	cout << "\n" << "Penult Coupon Date: ";
	dow(penultimate_coupon_date);
	cout << "\n" << "Maturity Date: ";
	dow(maturity_date);
	cout << "\n\n";

	Bond bond_20_yr{ bond_id,dated_date,first_coupon_date,
	penultimate_coupon_date,maturity_date,coupon_frequency,coupon_rate,face_value };

	ChronoDate yc_settle_date{ 2023,10,10 };

	vector<ChronoDate> unit_bond_maturity_dates
	{
		{2023, 10, 11}, {2024, 1, 10}, {2024, 4, 10}, {2024, 10, 10}, {2025, 10, 10}, {2026, 10, 12},
		{2028, 10, 10}, {2030, 10, 10}, {2033, 10, 10}, {2038, 10, 11}, {2043, 10, 12}, {2053, 10, 10}
	};

	vector<double> unit_bond_prices
	{
		0.999945, 0.994489, 0.98821, 0.973601, 0.939372, 0.901885,
		0.827719, 0.759504, 0.670094, 0.547598, 0.448541, 0.300886
	};

	LinearInterpYieldCurve yc{ yc_settle_date, unit_bond_maturity_dates, unit_bond_prices };

	ChronoDate bond_settle_date = yc_settle_date;

	double value = bond_20_yr.discounted_value(bond_settle_date, yc);
	cout << std::fixed << std::setprecision(2);
	cout << "Present value of bond = " << value << endl << endl;


}