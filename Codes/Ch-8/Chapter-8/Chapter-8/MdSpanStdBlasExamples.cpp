#define MDSPAN_USE_PAREN_OPERATOR 1

#include "ExampleDeclarations.h"
#include <mdspan>
#include <linalg>
#include <experimental/linalg>
#include <vector>

#include <cstdlib>

#include <iostream>
using std::cout;
using std::endl;

#include <format>
using std::format;

namespace stdex = std::experimental;

void md_span_and_std_blas_examples()
{
	using std::vector;
	using std::size_t;

	fixed_dim_symm_mtx();

	vector<double> w{ 10.1,10.2,10.3,10.4,10.5,10.6 };
	size_t m = 3;
	size_t n = 2;
	print_dynamic_mdspan(m, n, w);

	submdspan_examples();
	std_blas_mtx_vector_prod();
}

void fixed_dim_symm_mtx()
{
	cout << "*** fixed_dim_symm_mtx() ***" << endl << endl;
	using std::vector, std::size_t;

	vector v{ 101,102,103,104,105,106 };

	std::mdspan mds_01{ v.data(),3,1 };
	size_t n_rows = mds_01.extent(0);
	size_t n_cols = mds_01.extent(1);
	size_t n_extents = mds_01.rank();

	cout << format("num rows = {}, num cols = {}, num extents = {}",
		n_rows, n_cols, n_extents);

	for (size_t i = 0; i < n_rows; i++)
	{
		for (size_t j = 0; j < n_cols; ++j)
			cout << mds_01(i, j) << "\t";

		cout << endl;
	}

	cout << endl << endl;


	const auto mds_02 = std::mdspan{ v.data(),2,3 };

	for (size_t i = 0; i < mds_02.extent(0); i++) {
		for (size_t j = 0; j < mds_02.extent(1); ++j)
			cout << mds_02(i, j) << "\t";
		cout << endl;
	}

	cout << endl << endl;

	v[5] = 419;

	for (size_t i = 0; i < mds_01.extent(0); ++i)
	{
		for (size_t j = 0; j < mds_01.extent(1); ++j)
			cout << mds_01(i, j) << "\t";
		cout << endl;
	}
	cout << endl << endl;

	for (size_t i = 0; i < mds_02.extent(0); ++i)
	{
		for (size_t j = 0; j < mds_02.extent(1); ++j)
			cout << mds_02(i, j) << "\t";
		cout << endl;
	}
	cout << endl << endl;
}

void print_dynamic_mdspan(size_t m, size_t n, const std::vector<double>& v)
{
	cout << endl << "*** dynamic_mdspan(" << m << ", " << n << ")*** " << endl;
	using std::vector, std::size_t;
	std::mdspan md{ v.data(),std::extents{m,n} };

	for (size_t i = 0; i < md.extent(0); ++i)
	{
		for (size_t j = 0; j < md.extent(1); ++j)
			cout << md(i, j) << "\t";
		cout << endl;
	}
	cout << endl << endl;
}

void submdspan_exmaples()
{
	cout << endl << "*** sub_mdspan() ***" << endl;
	using std::vector, std::size_t;

	vector<int> v{ 101,102,103,104,105,106 };

	auto mds1 = std::mdspan{ v.data(),3,2 };
	size_t n_rows{ mds1.extent(0) };
	size_t n_cols{ mds1.extent(1) };
	size_t n_extents{ mds1.rank() };

	cout << std::format("num rows = {}, num cols = {}, num extents = {}",
		n_rows, n_cols, n_extents) << endl;

	for (size_t i = 0; i < mds1.extent(0); ++i) {
		for (size_t j = 0; j < mds1.extent(1); ++j)
			cout << mds1(i, j) << "\t";
		cout << endl;
	}
	

}