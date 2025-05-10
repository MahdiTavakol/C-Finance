#include <array>

enum class PayoffType
{
	Call = 1,
	Put = -1
};

class BlackScholes
{
public:
	BlackScholes(double strike, double spot, double time_to_exp,
		PayoffType payoff_type, double rate, double div = 0.0);

	double operator()(double vol) const;

private:
	std::array<double, 2> compute_norm_args_(double vol) const;

	double strike_, spot_, time_to_exp_;
	PayoffType payoff_type_;
	double rate_, div_;
};