#pragma once

#include <chrono>

class Timer
{
	using clock = std::chrono::steady_clock;
	using millisec = std::chrono::duration<double, std::milli>;
	using sec = std::chrono::duration<double>;

public:
	Timer() {}
	void start() { start_ = clock::now();}
	void stop() { stop_ = clock::now(); }
	double milliseconds() const
	{
		return std::chrono::duration_cast<millisec>(stop_ - start_).count();
	}

	double seconds() const
	{
		return std::chrono::duration_cast<sec>(stop_ - start_).count();
	}



private:
	std::chrono::time_point<clock> start_, stop_;
};
