#ifndef DUNJUN_TICKCOUNTER_HPP
#define DUNJUN_TICKCOUNTER_HPP

#include <Dunjun/Clock.hpp>

namespace Dunjun
{
class TickCounter
{
public:
	b8 update(f64 period)
	{
		b8 reset = false;
		if (m_clock.getElapsedTime() >= period)
		{
			m_tickRate = m_tick * (1.0 / period);
			m_tick = 0;
			reset = true;
			m_clock.restart();
		}

		m_tick++;

		return reset;
	}

	inline usize getTickRate() const { return m_tickRate; }

private:
	usize m_tick = 0;
	usize m_tickRate = 0;
	Clock m_clock;
};

} // namespace Dunjun

#endif
