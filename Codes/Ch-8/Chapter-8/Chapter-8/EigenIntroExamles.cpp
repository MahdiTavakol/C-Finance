#include "ExampleDeclarations.h"
#include <Eigen/Dense>
#include <cmath>
#include <complex>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <functional>
#include <random>
#include <vector>
#include <utility>
#include <format>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::RowVectorXd;

void eigen_intro_examples()
{
	fixed_dim_matrices();
	construct_dynamic_matrix();
	vector_and_row_vector();
	products();
	problem_with_auto();
	portfolio_example();
	dot_products();
	addition_and_subtraction();
}

void fixed_dim_matrices()
{
	cout << "*** fixed_dim_matrices() ***" << endl << endl;
	Eigen::Matrix3d dbl_mtx
	{
		{10.64,41.28,21.63},
		{41.95,87.45,13.68},
		{22.47,57.34,8.631}
	};
	Eigen::Matrix4i int_mtx
	{
		{24,0,23,13},
		{8,75,0,98},
		{11,60,1,3},
		{422,55,11,55}
	};
	cout << dbl_mtx << endl << endl;
	cout << int_mtx << endl << endl;

	cout << "First column of double prec mtx:\n" << dbl_mtx.col(0) << std::endl;
	cout << "Third row of int mtx:\n" << int_mtx.row(2) << endl << endl;
}

void construct_dynamic_matrix()
{
	cout << "*** construct_dynamic_matrix() ***" << endl << endl;

	MatrixXd mtx_01
	{
		{1.0,2.0,3.0},
		{4.0,5.0,6.0},
		{7.0,8.0,9.0},
		{10.0,11.0,12.0}
	};

	cout << "Contents of matrix mtx_01 are:\n" << mtx_01 << endl;

	MatrixXd mtx_02{};
	mtx_02.resize(2, 2);
	mtx_02 << 10.0, 12.0, 14.0, 16.0;
	cout << "Contents of matrix mtx_02 are:\n" << mtx_02 << endl;

	MatrixXd mtx_03{ 4,3 };

	mtx_03 << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0;
	cout << "Contents of matrix mtx_03 are:\n" << mtx_03 << endl;

	MatrixXd mtx_04{ 2,2 };
	mtx_04(0, 0) = 3.0;
	mtx_04(1, 0) = 2.5;
	mtx_04(0, 1) = -1.0;
	mtx_04(1, 1) = mtx_04(1, 0) + mtx_04(0, 1);
	cout << mtx_01.col(0) << endl << endl;
	cout << mtx_01.row(2) << endl << endl;

	VectorXd first_col_vec{ mtx_01.col(0) };
	RowVectorXd third_row_vec = mtx_01.row(2);

	cout << "First column of mtx as VectorXd:\n";
	cout << first_col_vec << endl << endl;

	cout << "Third row of mtx as RowVectorXd:\n";
	cout << third_row_vec << endl << endl;

	cout << "Is a block owning or a mutating view? (1st show original matrix):\n";
	cout << mtx_01 << endl << endl;
	auto first_row = mtx_01.row(0);
	first_row(0) = -100.0;
	cout << "Was the original matrix modified: (row 1, col 1) = -100.0 (ans: yes)\n";
	cout << mtx_01 << endl;

	cout << "What if we construct MatrixXd from a block?\n";
	MatrixXd first_row_matrix{ first_row };
	cout << first_row_matrix << endl << endl;
	cout << "What if we change the 1st element of first_row to -200.0, what happens to first_row_matrix (ans:nothing)\n";
	first_row(0) = -200.0;
	cout << first_row_matrix << endl << endl;
	cout << "What about the original mtx from  which the row block was taken?(ans: it is modified (-200.0))\n";
	cout << mtx_01 << endl;

	cout << endl << endl;
 }

void vector_and_row_vector()
{
	cout << "*** vector_and_row_vector() ***" << endl << endl;

	VectorXd vec_01{ {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0} };
	cout << "Contents of the VectorXd vec are:\n" << vec_01 << endl << endl;

	VectorXd vec_02{ 12 };

	vec_02 << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0;
	cout << "Contents of VectorXd vec_02 are:\n" << vec_02 << endl << endl;

	VectorXd vec_03{};
	vec_03.resize(4);
	vec_03 << 10.0, 12.0, 14.0, 16.0;
	cout << "Contents of VectorXd vec_03 are:\n" << vec_03 << endl << endl;

	VectorXd vec_04{ 3 };
	vec_04(0) = 3.19;
	vec_04(1) = 2.58;
	vec_04(2) = 10.87;
	cout << "Contents of the VectorXd vec_04 are:\n" << vec_04 << endl << endl;

	RowVectorXd b{ {1.0,2.0,3.0,4.0} };

	cout << "RowVectorXd b = " << b << endl << endl;

	cout << endl << endl;
}

void products()
{
	cout << "*** products() ***" << endl << endl;
	MatrixXd A
	{
		{1.0,2.0,3.0},
		{1.5,2.5,3.5},
		{4.0,5.0,6.0},
		{4.5,5.5,6.5},
		{7.0,8.0,9.0}
	};

	MatrixXd B
	{
		{1.0,2.0,3.0,4.0,5.0},
		{1.5,2.5,3.5,4.5,5.5},
		{5.0,6.0,7.0,8.0,8.5}
	};

	cout << "Matrix A:\n" << A << endl << endl << "Matrix B:\n" << B << endl << endl;


	MatrixXd prod_ab = A * B;
	cout << "A(5 X 3) * B(3 X 5) = " << endl << prod_ab << endl;
	cout << "Type = " << typeid(prod_ab).name() << endl << endl;

	MatrixXd scale_a = 0.5 * a;
	cout << "Scalar multiplication: 0.5*A" << endl;
	cout << scale_a << endl << endl;

	B.col(1) *= 2.0;
	cout << "Multiply 2nd column of B by 2:" << endl;
	cout << B << endl << endl;
	cout << "Type = " << typeid(B).name() << endl << endl;

	B *= 3.0;
	cout << "Scalar multiplication of matrix B by 3:\n";
	cout << B << endl << endl;
	cout << "Type = " << typeid(B).name() << endl << endl;

	MatrixXd cwise_prod = A.cwiseProduct(B.transpose());
	cout << "Elem by Elem: A(5X3) * B^T(5X3) = \n" << cwise_prod << endl << endl;
 }

void problem_with_auto()
{
	cout << "*** problem_with_auto() ***" << endl << endl;

	MatrixXd M
	{
		{1.0,2.0,3.0},
		{1.5,2.5,3.5},
		{4.0,5.0,6.0}
	};

	MatrixXd N
	{
		{10.0,20.0,30.0},
		{10.5,20.5,30.5},
		{40.0,50.0,60.0}
	};

	auto P = M * N;

	cout << "Matrix product type P: " << typeid(P).name() << endl;
	cout << P << endl << endl;

	N.row(0) *= 0.1;
	cout << "Now P = " << endl;
	cout << P << endl << endl;

	MatrixXd M2
	{
		{1.0,2.0,3.0},
		{1.5,2.5,3.5},
		{4.0,5.0,6.0}
	};

	MatrixXd N2
	{
		{10.0,20.0,30.0},
		{10.5,20.5,30.5},
		{40.0,50.0,60.0}
	};

	MatrixXd P2 = M2 * N2;
	cout << "MatrixXd product type P2: " << typeid(P2).name() << endl;
	cout << P2 << endl;

	N2.row(0) *= 0.1;
	cout << "Now P2 = " << endl;
	cout << P2 << endl << endl;
}

void portfolio_example()
{
	cout << "*** portfolio_example() ***" << endl;

	MatrixXd corr_mtx
	{
		{1.0,0.5,0.25},
		{0.5,1.0,-0.7},
		{0.25,-0.7,1.0}
	};

	VectorXd vols{ {0.2,0.1,0.4} };
	MatrixXd vol_mtx{ vols.asDiagonal() };
	cout << "Type of vols.asDiagonal():" << typeid(vols.asDiagonal()).name() << endl;

	MatrixXd cov_mtx = vols.asDiagonal() * corr_mtx * vols.asDiagonal();
	cout << "Covariance matrix type and contents: " << typeid(cov_mtx).name() << endl << cov_mtx << endl << endl;


	VectorXd fund_weights{ {0.6,-0.3,0.7} };
	double port_vol = std::sqrt(fund_weights.transpose() * cov_mtx * fund_weights);
	cout << "Portfolio volatility = " << port_vol << endl << endl;

}

void dot_products()
{
	cout << "*** dot_products() ***" << endl;

	VectorXd u{ {1.0,2.0,3.0} };
	VectorXd v{ {0.5,-0.5,1.0} };

	double dp = u.transpose() * v;
	MatrixXd op = u * v.transpose();

	cout << "u' * v = " << dp << endl << endl;
	cout << "u * v' = " << op << endl << endl;

	double dot_prod = u.dot(v);
	double dot_prod_rev = v.dot(u);
	cout << std::format("u dot v = {},v dot u = {}", dot_prod, dot_prod_rev) << endl << endl;
 }

void addition_and_substraction()
{
	cout << "*** addition_and_substraction() ***" << endl;


	MatrixXd A
	{
		{1.0, 2.0, 3.0},
		{1.5, 2.5, 3.5},
		{4.0, 5.0, 6.0},
		{4.5, 5.5, 6.5},
		{7.0, 8.0, 9.0}
	};

	MatrixXd C
	{
		{10.0, 20.0, 30.0},
		{10.5, 20.5, 30.5},
		{40.0, 50.0, 60.0},
		{40.5, 50.5, 60.5},
		{70.0, 80.0, 90.0}
	};


	MatrixXd mtx_sum = A + C;
	cout << "Sum of matrices:" << endl;
	cout << mtx_sum << endl << endl;

	VectorXd u{ {1.0,2.0,3.0} };
	VectorXd v{ {0.5,-0.5,1.0} };

	VectorXd vec_diff = v - u;
	cout << "Vector difference:" << endl;
	cout << vec_diff << endl << endl;
}