#pragma once

#include <vector>
#include <cstdlib>
#include <utility>
#include <cassert>
#include <iostream>
#include <format>

template<typename U, typename V>
class VectorAddExpr
{
public:
	VectorAddExpr(const U& u_, const V& v_) : u{ u_ }, v{ v_ }
	{
		assert(u.size() == v.size());
	}

	double operator[](size_t idx) const
	{
		return u[idx] + v[idx];
	}

	std::size size() const {
		return u.size();
	}

	operator std::vector<double>() const
	{
		std::vector<double> result;
		result.reserve(this->size());

		for (size_t i = 0; i < this->size(); ++i)
			result.push_back(operator[](i));

		return result;
	}

private:
	const U& u;
	const V& v;
};

template<typename U, typename V>
VectorAddExpr<U, V> operator + (const U& u, const V& v) {
	return { u,v };
}