#pragma once
#include <iostream>

template <typename T>
void print_this(const T& t)
{
	std::cout << t << " ";
}

void engines_and_distributions();

void default_random_engine();
void mersenne_twister_and_normal_dist();
void other_distributions();
void shuffle_algo_example();
void max_drawdown_sim();


void mc_option_examples();

void euro_no_barrier_examples();
void euro_with_barrier_examples();

void parallel_stl_algorithms();

void parallel_min_max_mean();
void parallel_dot_product();
void exp_approx(unsigned num_elements, unsigned n);


void concurrency_examples();

void squares();

void mc_option_examples_parallel();
void par_barrier_same_as_no_par();
void perf_test_results_no_barrier();
void perf_test_results_with_barrier();
void euro_no_barrier_examples_par();
void euro_with_barrier_examples_par();
void euro_no_barrier_examples_compare_async();
void euro_with_barrier_examples_compare_async();
void perf_tests_euro_no_barrier_examples(double time_to_exp, int time_steps, int num_scenarios);
void perf_tests_euro_with_barrier_examples(double time_to_exp, int time_steps, int num_scenarios);


// MC Option pricing with async/future(s), single seed
//void mc_option_examples_parallel_one_seed();		// Top calling function
//void perf_test_results_no_barrier_one_seed();		// Sub-Top calling function
//void perf_test_results_with_barrier_one_seed();		// Sub-Top calling function		
//void perf_tests_euro_no_barrier_examples_one_seed(double time_to_exp, int time_steps, int num_scenarios);
//void perf_tests_euro_with_barrier_examples_one_seed(double time_to_exp, int time_steps, int num_scenarios);