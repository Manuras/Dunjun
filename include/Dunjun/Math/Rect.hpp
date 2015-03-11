#ifndef DUNJUN_MATH_RECT_HPP
#define DUNJUN_MATH_RECT_HPP

#include <Dunjun/Types.hpp>
#include <Dunjun/Math/Vector2.hpp>

namespace Dunjun
{
struct Rect
{
	Rect() = default;
	Rect(const Rect& other) = default;

	Rect(f32 x, f32 y, f32 width, f32 height);
	Rect(const Vector2& position, const Vector2& size);

	bool contains(const Vector2& point) const;
	bool intersects(const Rect& rectangle) const;
	bool intersects(const Rect& rectangle, Rect& intersection) const;

	f32 x = 0;
	f32 y = 0;
	f32 width = 0;
	f32 height = 0;
};

bool operator==(const Rect& left, const Rect& right);
bool operator!=(const Rect& left, const Rect& right);

} // namespace Dunjun

#endif
