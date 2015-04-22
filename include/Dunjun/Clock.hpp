#ifndef DUNJUN_CLOCK_HPP
#define DUNJUN_CLOCK_HPP

#include <Dunjun/Input.hpp>
#include <Dunjun/Time.hpp>
#include <thread>

namespace Dunjun
{
class Clock
{
public:
	inline Time getElapsedTime() const
	{
		return Input::getTime() - m_startTime;
	}

	inline Time restart()
	{
		Time now = Input::getTime();
		Time elapsed = now - m_startTime;
		m_startTime = now;

		return elapsed;
	}

private:
	Time m_startTime = Input::getTime();
};

inline void sleep(Time time)
{
	std::this_thread::sleep_for(std::chrono::microseconds(time.asMicroseconds()));
}
} // namespace Dunjun

#endif
