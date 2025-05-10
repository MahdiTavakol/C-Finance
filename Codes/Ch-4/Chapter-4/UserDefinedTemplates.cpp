
#include "Ch04_example_functions.h"
#include "UserDefinedTemplates.h"
#include "Fraction.h"
#include "Shapes.h"
#include "BlackScholes.h"
#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <format>

void user_defined_template_examples()
{
	fcn_template_examples();
	class_template_examples();
	default_tmpl_param_example();
}

void fcn_template_examples()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** fcn_template_examples() ***\n";

	cout << "Test Frac *:\n";
	auto prod = Fraction{ 2,3 }*Fraction{ 1,2 };
	cout << format("Test prod = {}/{}\n\n", prod.numer(), prod.denom());

	int sq_int = tmpl_square(4);
	int sq_real = tmpl_square(4.2);
	cout << format("Square of ints = {}, square of reals = {}\n\n", sq_int, sq_real);

	Fraction frac{ 2,3 };
	Fraction sq_frac = tmpl_square(frac);
	cout << format("Square of fraction {}/{} is {}/{}\n\n", frac.numer(), frac.denom(), sq_frac.numer(), sq_frac.denom());

	auto sq_frac_unif = tmpl_square<Fraction>({ 2,3 });
	cout << format("Square of fraction using unif initialization = {}/{}\n\n",
		sq_frac_unif.numer(), sq_frac_unif.denom());

	Circle circ{ 1.0 };

	cout << "\n\n";

}

void class_template_examples()
{
	using std::vector, std::cout, std::format;
	cout << "\n*** class_template_examples() ***\n";

	MyPair<int> mp_int{ 10,26 };
	int min_int = mp_int.get_min();

	MyPair<Fraction> mp_frac{ {3,2},{5,11} };
	Fraction min_frac = mp_frac.get_min();

	cout << format("Min(10, 26) = {}, Min(3/2, 5/11) = {}/{}\n", min_int, min_frac.numer(), min_frac.denom());
}

void default_tmpl_param_example()
{
	using std::cout, std::format;

	cout << "\n*** default_tmpl_param_example() ***\n";

	MyPair<> real_pair{ 19.73,10.26 };
	double min_val = real_pair.get_min();

	cout << format("Min real value ={}\n\n", min_val);
}