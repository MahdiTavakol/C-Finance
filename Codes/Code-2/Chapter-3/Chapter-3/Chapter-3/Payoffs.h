#pragma once
#include <memory>


class Payoff03
{
public:
	virtual double payoff03(double price) const = 0;
	virtual Payoff03* clone() const = 0; // New
	virtual ~Payoff03() = default;
};


class CallPayoff03 final : public Payoff03
{
public:
	CallPayoff03(double strike);
	double payoff03(double price) const override;
	CallPayoff03* clone() const override; // New

private:
	double strike_;
};

class PutPayoff03 final : public Payoff03
{
public:
	PutPayoff03(double strike);
	double payoff03(double price) const override;
	PutPayoff03* clone() const override;

private:
	double strike_;
};

class Payoff
{
public:
	virtual double payoff(double price) const = 0;
	virtual std::unique_ptr<Payoff> clone() const = 0;
	virtual ~Payoff() = default;
};

class CallPayoff final : public Payoff
{
public:
	CallPayoff(double strike);
	double payoff(double price) const override;
	std::unique_ptr<Payoff> clone() const override;

private:
	double strike_;
};

class PutPayoff final : public Payoff
{
public:
	PutPayoff(double strike);
	//double operator()(double spot) const override;
	double payoff(double price) const override;
	std::unique_ptr<Payoff> clone() const override;

private:
	double strike_;
};