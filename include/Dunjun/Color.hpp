#ifndef DUNJUN_COLOR_HPP
#define DUNJUN_COLOR_HPP

#include <Dunjun/Types.hpp>

namespace Dunjun
{
struct Color
{
	explicit Color(u8 r, u8 g, u8 b, u8 a = 0xFF)
	: r(r)
	, g(g)
	, b(b)
	, a(a)
	{
	}

	explicit Color(u32 rgba)
	{
		r = (rgba >> 24) & 0xFF;
		g = (rgba >> 16) & 0xFF;
		b = (rgba >> 8) & 0xFF;
		a = (rgba >> 0) & 0xFF;
	}

	union
	{
		u8 data[4];
		struct
		{
			u8 r, g, b, a;
		};
	};
};
}

#endif
