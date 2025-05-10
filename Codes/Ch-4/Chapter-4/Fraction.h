#pragma once

#include <compare>

class Fraction
{
public:
	Fraction(int n, int d);

	bool operator == (const Fraction& rhs) const = default;
	std::strong_ordering operator <=> (const Fraction& rhs) const;

	int numer() const;
	int denom() const;

	Fraction operator *(const Fraction& rhs) const;

private:
	int n_, d_;

};