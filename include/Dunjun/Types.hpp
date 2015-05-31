#ifndef DUNJUN_TYPES_HPP
#define DUNJUN_TYPES_HPP

#include <cstddef>
#include <cstring>
#include <memory>

namespace Dunjun
{
// Type Specification
// Integer:        [us](8|16|32|64)
// Floating Point: f(16|32|64)
// Integral Size:  usize
// Boolean:        b(8|32)

// All "common" platforms use the same size for char, short and int
// We do not need to include stdint.h/cstdint which not always available.

// The amount of times that I have swapped between conventions is a lot!
// s8/i8/int8 etc. & u8/uint8 etc.
using s8 = signed char;
using u8 = unsigned char;

using s16 = signed short;
using u16 = unsigned short;

using s32 = signed int;
using u32 = unsigned int;

// Older versions of MSVC do not defined long long as 64 bits so just in case
#if defined(_MSC_VER)
	using s64 = signed __int64;
	using u64 = unsigned __int64;
#else
	using s64 = signed long long;
	using u64 = unsigned long long;
#endif

// Depending on the header, `size_t` xor `std::size_t` may defined
using usize = std::size_t;

// NOTE(bill): Prefer `bool` as it indicates it is an boolean type
// Only use b8/b32 if you want a boolean type of a certain size
using b8 = s8;
using b32 = s32;

using f32 = float;
using f64 = double;

namespace
{
// TODO(bill): May not be complete - Handling NaN/+-inf
inline s16 f32Tof16(f32 f)
{
	s16 fint16;
	s32 fint32;
	std::memcpy(&fint32, &f, sizeof(f32));
	fint16 = ((fint32 & 0x7fffffff) >> 13) - (0x38000000 >> 13);
	fint16 |= ((fint32 & 0x80000000) >> 16);

	return fint16;
}

// TODO(bill): May not be complete - Handling NaN/+-inf
inline f32 f16Tof32(s16 fint16)
{
	s32 fint32 = ((fint16 & 0x8000) << 16);
	fint32 |= ((fint16 & 0x7fff) << 13) + 0x38000000;

	f32 fRet;
	std::memcpy(&fRet, &fint32, sizeof(f32));
	return fRet;
}
} // namespace (anonymous)

class f16
{
public:
	f16()
	: m_value{0}
	{
	}

	f16(f32 f)
	: m_value{f32Tof16(f)}
	{
	}

	f16(const f16& f) = default;
	f16(f16&& f)
	: m_value{std::move(f.m_value)}
	{
	}

	operator f32() { return f16Tof32(m_value); }
	operator f32() const { return f16Tof32(m_value); }

	f16& operator=(const f16& f) { m_value = f; return *this; }
	f16& operator+=(const f16& f)
	{
		*this = *this + f;
		return *this;
	}
	f16& operator-=(const f16& f)
	{
		*this = *this - f;
		return *this;
	}
	f16& operator*=(const f16& f)
	{
		*this = *this * f;
		return *this;
	}
	f16& operator/=(const f16& f)
	{
		*this = *this / f;
		return *this;
	}
	f16& operator-()
	{
		*this = f16{-static_cast<f32>(*this)};
		return *this;
	}

	friend f16 operator+(const f16& a, const f16& b);
	friend f16 operator-(const f16& a, const f16& b);
	friend f16 operator*(const f16& a, const f16& b);
	friend f16 operator/(const f16& a, const f16& b);

protected:
	s16 m_value;
};

inline f16 operator+(const f16& a, const f16& b)
{
	return {static_cast<f32>(a) + static_cast<f32>(b)};
}
inline f16 operator-(const f16& a, const f16& b)
{
	return {static_cast<f32>(a) - static_cast<f32>(b)};
}
inline f16 operator*(const f16& a, const f16& b)
{
	return {static_cast<f32>(a) * static_cast<f32>(b)};
}
inline f16 operator/(const f16& a, const f16& b)
{
	return {static_cast<f32>(a) / static_cast<f32>(b)};
}
} // namespace Dunjun
#endif
