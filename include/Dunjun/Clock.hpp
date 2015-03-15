#ifndef DUNJUN_CLOCK_HPP
#define DUNJUN_CLOCK_HPP

#include <Dunjun/Input.hpp>
#include <Dunjun/Types.hpp>

namespace Dunjun
{
class Clock
{
public:
	inline f64 getElapsedTime() const { return Input::getTime() - m_startTime; }

	inline f64 restart()
	{
		f64 now = Input::getTime();
		f64 elapsed = now - m_startTime;
		m_startTime = now;

		return elapsed;
	}

private:
	f64 m_startTime = Input::getTime();
};
} // namespace Dunjun

#endif
