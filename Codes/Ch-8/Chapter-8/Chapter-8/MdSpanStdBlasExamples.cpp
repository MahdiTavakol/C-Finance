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

	auto row_1 = stdex::submdspan(mds1, 0, stdex::full_extent);
	auto col_2 = stdex::submdspan(mds1, stdex::full_extent, mds.extent(1) - 1);

	cout << endl << typeid(row_1).name() << endl;
	cout << row_1[0] << endl << endl;

	cout << "1st row (index = 0):" << endl;
	for (size_t k = 0; k < row_1.extent(0); ++k)
		cout << format("row_1[{}] = {}", k, row_1[k]) << "\t";

	cout << endl << endl;

	cout << "2nd column (index = 1): " << endl;
	for (size_t k = 0; k < col_2.extent(0), ++k)
		cout << format("col_2[{}] = {}", k, col_2[k]) << "\t";

	cout << "Modify last element of 2nd column submdspan; what happens to original mdspan?:" << endl;
	col_2[2] = 3333;

	for (size_t i = 0; i < n_rows; ++i)
	{
		for (size_t j = 0; j < n_cols; j++)
			cout << mds1(i, j) << "\t";
		cout << endl;
	}

	cout << endl << endl;

	cout << "The original std::vector v is also modified:" << endl;
	for (int x : v)
		cout << x << " ";

	cout << endl << endl;
	

}

void std_blas_mtx_vector_prod()
{
	cout << endl << "*** std_blas_mtx_vector_prod() ***" << endl;

	using std::vector, std::size_t;
	namespace stdex = std::experimental;

	constexpr size_t m = 2;
	constexpr size_t n = 3;

	std::vector<double> A_vec(m * n);
	std::vector<double> x_vec(n);

	A_vec = { 1.0, 2.0,3.0,4.0,5.0,6.0 };
	x_vec = { 1.0,2.0,3.0 };

	print_dynamic_mdspan(m, n, A_vec);

	std::vector<double> y_vec(n);

	mdspan A{ A_vec.data(),m,n };
	mdspan x{ x_vec.data(),n };
	mdspan y{ y_vec.data(),m };

	stdex::linalg::matrix_vector_product(A, x, y);

	cout << "Mtx-vector prod Ax = \n";
	for (size_t j = 0; j < m; j++)
		cout << y(j) << " ";

	cout << endl << endl;
}