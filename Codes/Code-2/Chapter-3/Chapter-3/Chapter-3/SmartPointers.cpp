#include "Ch03_example_functions.h"

SimpleClass::SimpleClass(int k) : k_{ k }
{}

int SimpleClass::get_val() const
{
	return k_;
}

void SimpleClass::reset_val(int k)
{
	k_ = k;
}