#include "ExampleDeclarations.h"

#include <utility>
#include <vector>
#include <random>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <format>

using std::vector;
using std::cout;
using std::endl;
using std::format;

void lazy_evaluation_demonstration()
{
	cout << "*** lazy_evalulation_demonstration() ***" << endl;
	naive_vector_addition();
	sum_by_element();
	lazy_vector_addition();
	cout << endl << endl;
}

std::vector<double> operator +(const std::vector<double>& a,
	const std::vector<double>& b)
{
	assert(a.size() == b.size());
	std::vector<double> result;
	result.reserve(a.size());
	for (size_t i = 0; i < a.size(); i++)
		result.push_back(a[i] + b[i]);
	return result;
}

void naive_vector_addition()
{
	cout << "*** naive_vector_addition() ***" << endl;
	vector<double> v_01{ 1.0,2.0,3.0 };
	vector<double> v_02{ 1.5,2.5,3.5 };
	vector<double> v_03{ 4.0,5.0,6.0 };
	vector<double> v_04{ 4.5,5.5,6.5 };
	auto y = v_01 + v_02 + v_03 + v_04;
	for (double x : y)
		cout << x << " ";
	cout << endl << endl;
}

std::vector<double> sum_four_vectors(const std::vector<double>& a,
	const std::vector<double>& b, const std::vector<double>& c,
	const std::vector<double>& d)
{
	assert(a.size() == b.size());
	assert(b.size() == c.size());
	assert(c.size() == d.size());

	std::vector<double> sum(a.size());
	for (size_t i = 0; i < a.size(); i++)
		sum[i] = a[i] + b[i] + c[i] + d[i];

	return sum;
}

void sum_by_elements()
{
	cout << "*** sum_by_elements() ***" << endl;
	vector<double> v_01{ 1.0, 2.0, 3.0 };
	vector<double> v_02{ 1.5, 2.5, 3.5 };
	vector<double> v_03{ 4.0, 5.0, 6.0 };
	vector<double> v_04{ 4.5, 5.5, 6.5 };

	auto y = sum_four_vectors(v_01, v_02, v_03, v_04);

	for (double x : y)
		cout << x << " ";

	cout << endl << endl;
 }

class SumOfFourVectors
{
public:
	SumOfFourVectors(const std::vector<double>& a_,
		const std::vector<double>& b_,
		const std::vector<double>& c_,
		const std::vector<double>& d_) :
		a{ a_ }, b{ b_ }, c{ c_ }, d{ d_ }
	{
		assert(a.size() == b.size());
		assert(b.size() == c.size());
		assert(c.size() == d.size());
	}

	double operator[](size_t i) const
	{
		return a[i] + b[i] + c[i] + d[i];
	}

private:
	const std::vector<double> a, b, c, d;
};

void lazy_vector_addition()
{
	cout << "*** lazy_vector_addition() ***" << endl;
	vector<double> v_01{ 1.0, 2.0, 3.0 };
	vector<double> v_02{ 1.5, 2.5, 3.5 };
	vector<double> v_03{ 4.0, 5.0, 6.0 };
	vector<double> v_04{ 4.5, 5.5, 6.5 };

	SumOfFourVectors y{ v_01,v_02,v_03,v_04 };

	vector<double> vec_sum{ y[0],y[1],y[2] };
	cout << "Lazy sum of all four vectors" << endl;
	for (double x : vec_sum)
	{
		cout << x << " ";
	}
	cout << endl << endl;

	double sum_of_1st_elems = y[0];
	double sum_of_3rd_elems = y[2];

	cout << format("Lazy sums of 1st and 3rd elements only: {}, {}",
		sum_of_1st_elems, sum_of_3rd_elems);
	cout << endl << endl;
}