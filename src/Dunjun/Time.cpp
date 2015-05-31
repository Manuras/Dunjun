#include <Dunjun/Config.hpp>
#include <Dunjun/Time.hpp>

#include <thread>

#if defined(DUNJUN_COMPILER_MSVC)
	#include <Windows.h>
#endif


namespace Dunjun
{
const Time Time::Zero{0};

f32 Time::asSeconds() const { return m_microseconds.count() / 1000000.0f; }

s32 Time::asMilliseconds() const
{
	return static_cast<s32>(m_microseconds.count() / 1000);
}

s64 Time::asMicroseconds() const { return m_microseconds.count(); }

#if defined(DUNJUN_COMPILER_MSVC)
namespace
{
INTERNAL LARGE_INTEGER getFrequency()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}
} // namespace (anonymous)

Time Time::now()
{
	// NOTE(bill): std::chrono does not have a good enough precision in MSVC12
	// and below. This may have been fixed in MSVC14 but unsure as of yet.

	// Force the following code to run on first core
	// NOTE(bill): See http://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx
	HANDLE currentThread{GetCurrentThread()};
	DWORD_PTR previousMask{SetThreadAffinityMask(currentThread, 1)};

	// Get the frequency of the performance counter
	// It is constant across the program's lifetime
	LOCAL_PERSIST LARGE_INTEGER s_frequency = getFrequency();

	// Get the current time
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	// Restore the thread affinity
	SetThreadAffinityMask(currentThread, previousMask);

	return microseconds(1000000 * time.QuadPart / s_frequency.QuadPart);
}
#else
Time Time::now()
{
	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();

	return microseconds(
		std::chrono::duration_cast<std::chrono::microseconds>(now).count());
}
#endif

void Time::sleep(Time time)
{
	std::this_thread::sleep_for(
	    std::chrono::microseconds(time.asMicroseconds()));
}

Time::Time(s64 microseconds)
: m_microseconds{std::chrono::microseconds{microseconds}}
{
}

Time seconds(f32 amount) { return Time{static_cast<s64>(amount * 1000000)}; }

Time milliseconds(s32 amount) { return Time{static_cast<s64>(amount * 1000)}; }

Time microseconds(s64 amount) { return Time{amount}; }

bool operator==(Time left, Time right)
{
	return left.asMicroseconds() == right.asMicroseconds();
}

bool operator!=(Time left, Time right)
{
	return left.asMicroseconds() != right.asMicroseconds();
}

bool operator<(Time left, Time right)
{
	return left.asMicroseconds() < right.asMicroseconds();
}

bool operator>(Time left, Time right)
{
	return left.asMicroseconds() > right.asMicroseconds();
}

bool operator<=(Time left, Time right)
{
	return left.asMicroseconds() <= right.asMicroseconds();
}

bool operator>=(Time left, Time right)
{
	return left.asMicroseconds() >= right.asMicroseconds();
}

Time operator-(Time right) { return microseconds(-right.asMicroseconds()); }

Time operator+(Time left, Time right)
{
	return microseconds(left.asMicroseconds() + right.asMicroseconds());
}

Time operator-(Time left, Time right)
{
	return microseconds(left.asMicroseconds() - right.asMicroseconds());
}

Time& operator+=(Time& left, Time right) { return left = left + right; }

Time& operator-=(Time& left, Time right) { return left = left - right; }

Time operator*(Time left, f32 right)
{
	return seconds(left.asSeconds() * right);
}

Time operator*(Time left, s64 right)
{
	return microseconds(left.asMicroseconds() * right);
}

Time operator*(f32 left, Time right)
{
	return seconds(left * right.asSeconds());
}

Time operator*(s64 left, Time right)
{
	return microseconds(right.asMicroseconds() * left);
}

Time& operator*=(Time& left, f32 right) { return left = left * right; }

Time& operator*=(Time& left, s64 right) { return left = left * right; }

Time operator/(Time left, f32 right)
{
	return seconds(left.asSeconds() / right);
}

Time operator/(Time left, s64 right)
{
	return microseconds(left.asMicroseconds() / right);
}

Time& operator/=(Time& left, f32 right) { return left = left / right; }

Time& operator/=(Time& left, s64 right) { return left = left / right; }

f32 operator/(Time left, Time right)
{
	return left.asSeconds() / right.asSeconds();
}

Time operator%(Time left, Time right)
{
	return microseconds(left.asMicroseconds() % right.asMicroseconds());
}

Time& operator%=(Time& left, Time right) { return left = left % right; }

} // namespace Dunjun
