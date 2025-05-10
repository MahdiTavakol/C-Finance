#pragma once

void intro_and_other_stl_algos();

bool is_odd(int n);

void first_example_count_if();
void first_ex_with_other_containers();
void first_ex_with_ranges();

void commonly_used_algorithms();
void for_each_examples();
void transform_examples_same_container();
void transform_examples_different_container();
void std_begin_and_std_end();

class Quadratic
{
public:
	Quadratic(double a, double b, double c) :
		a_{ a }, b_{ b }, c_{ c } {}

	double operator()(double x) const
	{
		return (a_ * x + b_) * x + c_;
	}

	double value(double x) const
	{
		return (a_ * x + b_) * x + c_;
	}

private:
	double a_, b_, c_;
};

void class_functor_as_aux_fcn();
void member_fcn_as_aux_fcn();

void algo_examples_in_chptr_summary();

void locate_sort_search_copy_move();
void count_and_count_if();
void max_min_elements();
void sorting_values();
void searching_containers();
void binary_search_examples();
void copy_and_move();

void numerical_algorithms();
void iota_examples();
void accumulate_and_inner_product_examples();
void partial_sum_examples();
void adj_diff_examples();
void fold_left_examples();

void vwap_example();
void logs_of_adj_diff_divisions();
void adj_diffs_of_logs();

void range_view_examples();
void indiv_views();
void chain_views();
void range_based_views();
void views_containers_loops();