#pragma once
#include <iostream>

template <typename T>
T tmpl_square(const T& t);

template <typename T>
T tmpl_square(const T& t)
{
	return t * t;
}

template<typename T>
void print_this(T t)
{
	std::cout << t << " ";
}