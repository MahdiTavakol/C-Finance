#pragma once

#include <iostream>

template <typename T>
T tmpl_square(const T& t);

template <typename T>
T tmpl_square(const T& t)
{
	return t * t;
}

template <typename T = double>
class MyPair
{
public:
	MyPair(T first, T second);
	T get_min() const;

private:
	T a_, b_;
};

template <typename T>
MyPair<T>::MyPair(T first, T second) : a_{ first }, b_{ second } {}

template<typename T>
T MyPair<T>::get_min() const
{
	return a_ < b_ ? a_ : b_;
}

template<typename T>
void print_this(T t)
{
	std::cout << t << " ";
}