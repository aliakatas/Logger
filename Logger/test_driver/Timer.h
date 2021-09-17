#pragma once

#include <chrono>			// for std::chrono functions

/** Class to provide timing functionality to 
host code. It should not be relied upon for 
measuring pure GPU code. It is used only
for reporting purposes to the user.
*/
class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >; // needs update with common extension (seconds??). ratio refers to ticks => cannot map to seconds accurately?

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer();

	void reset();

	double elapsed() const;
};