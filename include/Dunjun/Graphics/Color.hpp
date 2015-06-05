#ifndef DUNJUN_GRAPHICS_COLOR_HPP
#define DUNJUN_GRAPHICS_COLOR_HPP

#include <Dunjun/Common.hpp>

namespace Dunjun
{
struct Color
{
	GLOBAL const u32 Depth{256};

	explicit Color(u8 r, u8 g, u8 b, u8 a = (u8)0xFF)
	: r{r}
	, g{g}
	, b{b}
	, a{a}
	{
	}

	explicit Color(u32 rgba)
	{
		r = (rgba >> 24) & 0xFF;
		g = (rgba >> 16) & 0xFF;
		b = (rgba >> 8)  & 0xFF;
		a = (rgba >> 0)  & 0xFF;
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
