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
#include <iomanip>

using std::vector;
using std::cout;
using std::setprecision;

using Eigen::MatrixXd;
using Eigen::VectorXd;

void eigen_decomposition_examples()
{
	qr_linear_regression();
	cholesky_correlated_random_equity_paths();
	principal_components_mtx();

	solve_linear_system();
	jacobi_svd_linear_regression();
	linear_regression_with_intercept();
}

void qr_linear_regression()
{
	cout << "\n" << "*** qr_linear_regression() ***\n";

	MatrixXd X
	{
		{-0.044700, -0.007888,  0.042980,  0.016417, -0.017797, -0.016714,
		  0.019472,  0.029853,  0.023126, -0.033879, -0.003384, -0.018474,
		 -0.012510, -0.018348,  0.010627,  0.036669,  0.010811, -0.035572,
		  0.027474,  0.005406, -0.010159, -0.006146, -0.010327, -0.010435,
		  0.011127, -0.023794, -0.028009,  0.002182,  0.008683,  0.001440},

		{-0.019003,  0.026037,  0.037827,  0.010629, -0.008382,  0.001122,
		 -0.004494,  0.017305, -0.006106,  0.012175, -0.003305,  0.027220,
		 -0.036089, -0.002230, -0.015748, -0.020619, -0.011641,  0.023149,
		 -0.002291,  0.006288, -0.012038, -0.029259,  0.011219, -0.008847,
		 -0.033738,  0.020619, -0.012078,  0.015673,  0.041013,  0.052195},

		{-0.030629,  0.024919, -0.001716,  0.008562,  0.003407, -0.010824,
		 -0.010361, -0.009302,  0.008142, -0.004064,  0.000584,  0.004640,
		  0.031893, -0.013544, -0.023574, -0.004665, -0.006446, -0.005311,
		  0.045096, -0.007375, -0.005142, -0.001716, -0.005176, -0.002885,
		  0.002309, -0.014522, -0.017712,  0.001192, -0.002382, -0.004396}
	};

	X.transposeInPlace();

	VectorXd Y
	{
		{-0.039891,  0.001787, -0.016202,  0.056452,  0.003425, -0.012038,
		 -0.009998,  0.013452,  0.013486, -0.007898,  0.008111, -0.015425,
		 -0.002161, -0.028752,  0.011293, -0.007958, -0.004002, -0.031691,
		  0.026777,  0.009804,  0.000887,  0.014952, -0.004156, -0.001535,
		  0.013517, -0.021229,  0.001989, -0.020518,  0.005841,  0.011249}
	};

	VectorXd beta = X.householderQr().solve(Y);

	cout << setprecision(6)
		<< "The QR least-squares estimate of the regression coefficients (beta) is (solution of beta * X = Y):"
		<< "\n" << beta << "\n\n";
}

void cholesky_correlated_random_equity_paths()
{
	cout << "\n" << std::format("\n*** cholesky_correlated_random_equity_paths() ***") << "\n";

	MatrixXd cov_basket
	{
		{ 0.01263, 0.00025, -0.00017, 0.00503 },
		{ 0.00025, 0.00138,  0.00280, 0.00027 },
		{-0.00017, 0.00280,  0.03775, 0.00480 },
		{ 0.00503, 0.00027,  0.00480, 0.02900 }
	};

	Eigen::LLT<Eigen::MatrixXd> chol{ cov_basket };
	MatrixXd col_mtx = chol.matrixL();

	cout << "Cholesky Decomposition of cov_basket mtx: " << "\n";
	cout << setprecision(7) << chol_mtx << "\n\n";

	MatrixXd corr_scens{ 4,7 };
	corr_scens.col(0) << 100.0, 150.0, 25.0, 50.0;

	std::mt19937_64 mt_norm{ 100 };
	std::normal_distribution<> std_nd;

	auto std_norm = [&mt_norm, &std_nd](double x)
		{
			return std_nd(mt_norm);
		};

	Eigen::Block<MatrixXd> proj_vals_block =
		corr_scens(Eigen::seq(0, Eigen::last), Eigen::seq(1, Eigen::last));

	for (auto col : proj_vals_block.colwise())
	{
		std::ranges::transform(col, col.begin(), std_norm);
	}

	cout << "\nMatrix of N(0, 1) Random Draws (integ_scens): " << "\n";
	cout << std::fixed << setprecision(6) << corr_scens << "\n\n";

	proj_vals_block = chol_mtx * proj_vals_block;

	cout << "\nMatrix of N(0, 1) Random Draws (integ_scens) with spots in 1st col: " << "\n";
	cout << std::fixed << setprecision(6) << corr_scens << "\n\n";

	double rf_rate = 0.01;
	double time_to_maturity = 1.0;
	unsigned num_time_steps = 6;
	double dt = time_to_maturity / num_time_steps;

	auto gen_price = [dt, rf_rate](double price, double vol, double corr_norm)
		{
			double expArg1 = (rf_rate - ((vol * vol) / 2.0)) * dt;
			double expArg2 = corr_norm * std::sqrt(dt);
			double next_price = price * std::exp(expArg1 + expArg2);
			return next_price;
		};

	for (unsigned j = 1; j < corr_scens.cols(); ++j)
	{
		for (unsigned i = 0; i < corr_scens.rows(); ++i)
		{
			corr_scens(i, j) = gen_price(corr_scens(i, j - 1),
				cov_basket(i, i), corr_scens(i, j));
		}
	}


	cout << "Generated Random Price Paths (row --> path): " << "\n";
	cout << std::fixed << setprecision(2) << corr_scens << "\n\n";
}

void principal_components_mtx()
{
	cout << "\n" << std::format("\n*** principal_components_mtx() ***") << "\n";

	MatrixXd term_struct_cov_mtx
	{
		// 1 month   
		{0.018920,	0.009889, 0.005820,	0.005103, 0.003813,	0.003626,
			0.003136, 0.002646, 0.002015, 0.001438, 0.001303},

		// 3 months   
		{0.0, 0.010107, 0.006123, 0.004796, 0.003532, 0.003414,
			0.002893, 0.002404, 0.001815, 0.001217, 0.001109},

		// 6 months
		{0.0, 0.0, 0.005665, 0.004677, 0.003808, 0.003790,
			0.003255, 0.002771, 0.002179, 0.001567, 0.001400},

		// 1 year   
		{0.0, 0.0, 0.0, 0.004830, 0.004695, 0.004672,
			0.004126, 0.003606, 0.002952, 0.002238, 0.002007},

		// 2 years   
		{0.0, 0.0, 0.0, 0.0, 0.006431, 0.006338,
			0.005789, 0.005162, 0.004337, 0.003343, 0.003004},

		// 3 years   
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.006524,
			0.005947, 0.005356, 0.004540, 0.003568, 0.003231},

		// 5 years   
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.005800, 0.005291, 0.004552, 0.003669, 0.003352},

		// 7 years   
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.004985, 0.004346, 0.003572, 0.003288},

		// 10 years  
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.003958, 0.003319, 0.003085},

		// 20 years 
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.003062, 0.002858},

		// 30 years 
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.002814}
	};

	cout << "Original upper triangular covariance mtx :" << "\n";
	cout << std::fixed << setprecision(5) << term_struct_cov_mtx << "\n\n";

	Eigen::VectorXd cmplx_eigenvals =
		term_struct_cov_mtx.selfadjointView<Eigen::Upper>().eigenvalues();
	cout << "VectorXcd: " << typeid(cmplx_eigenvals).name() << "\n";

	cout << "The (complex) eigenvalues of the term structure covariance matrix are:\n "
		/*<< std::fixed << setprecision(6)*/ << cmplx_eigenvals << "\n\n";

	VectorXd eigenvals = cmplx_eigenvals.real();

	cout << "type of elem in eigenvals (real values): " << typeid(eigenvals).name() << "\n";
	cout << "Principal Components (Eigenvalues):" << "\n";

	for (auto ev : eigenvals)
	{
		cout << ev << " ";
	}
	cout << "\n\n";

	VectorXd eigenvals_alt = term_struct_cov_mtx.selfadjointView<Eigen::Upper>().eigenvalues().real();

	cout << "Principal Components (Eigenvalues) -- Alt method:" << "\n";
	for (auto ev : eigenvals_alt)
	{
		cout << ev << " ";
	}
	cout << "\n\n";

	eigenvals = eigenvals_alt;

	eigenvals = eigenvals / eigenvals.sum();
	auto wgt_eigenvals = eigenvals;

	std::ranges::sort(eigenval, std::greater());

	cout << "Weighted Principal Components (now stored in sorted eigenvals):" << "\n";
	for (auto wv : eigenvals)
	{
		cout << std::fixed << setprecision(5) << wv << " ";
	}
	cout << "\n\n";

	cout << "Cumulative Principal Component Weightings:" << "\n";
	double cum_value{ 0.0 };

	for (auto ev : eigenvals)
	{
		cum_value += ev;
		cout << cum_value << " ";
	}
	cout << "\n\n";

}

void solve_linear_systems()
{

}

