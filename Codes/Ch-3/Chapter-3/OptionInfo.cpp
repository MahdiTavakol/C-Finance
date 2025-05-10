#include "OptionInfo.h"


OptionInfo03::OptionInfo03(const Payoff03* payoff, double time_to_exp):
	payoff_ptr_{payoff->clone()}, time_to_exp_{time_to_exp} {}

OptionInfo03::~OptionInfo03()
{
	delete payoff_ptr_;
}

double OptionInfo03::option_payoff(double spot) const
{
	return payoff_ptr_->payoff03(spot);
}

double OptionInfo03::time_to_expiration() const
{
	return time_to_exp_;
}

OptionInfo03::OptionInfo03(const OptionInfo03& rhs) :
	payoff_ptr_{ rhs.payoff_ptr_->clone() },
	time_to_exp_{ rhs.time_to_expiration() } {}

OptionInfo03& OptionInfo03::operator=(const OptionInfo03& rhs)
{
	OptionInfo03{rhs}.swap(*this);
	return *this;
	/*
	if (this != &rhs)
	{
		delete payoff_ptr_;
		payoff_ptr_ = rhs.payoff_ptr_->clone();
		time_to_exp_ = rhs.time_to_expiration();
	}
	*/
}

void OptionInfo03::swap(OptionInfo03& rhs)
{
	using std::swap;
	swap(payoff_ptr_, rhs.payoff_ptr_);
	swap(time_to_exp_, rhs.time_to_exp_);
}

OptionInfo::OptionInfo(std::unique_ptr<Payoff> payoff, double time_to_exp) :
	payoff_ptr_{ std::move(payoff) }, time_to_exp_{ time_to_exp } {}

OptionInfo::OptionInfo(const OptionInfo& rhs) :
	payoff_ptr_{ rhs.payoff_ptr_->clone() },
	time_to_exp_{ rhs.time_to_expiration() } {}

double OptionInfo::option_payoff(double spot) const
{
	return payoff_ptr_->payoff(spot);
}

double OptionInfo::time_to_expiration() const
{
	return time_to_exp_;
}

void OptionInfo::swap(OptionInfo& rhs) noexcept
{
	using std::swap;
	swap(payoff_ptr_, rhs.payoff_ptr_);
	swap(time_to_exp_, rhs.time_to_exp_);
}

OptionInfo& OptionInfo::operator=(const OptionInfo& rhs)
{
	/* A temporaty OptionInfo object is created with OptionInfo{rhs}
	   which invokes the copy constructor with rhs values and then its contents
	   are swapped with *this so the rhs remains unchanged */
	OptionInfo{ rhs }.swap(*this);
	return *this;
}
