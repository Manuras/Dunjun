#ifndef DUNJUN_MATH_RECT_HPP
#define DUNJUN_MATH_RECT_HPP

#include <Dunjun/Types.hpp>
#include <Dunjun/Math/Vector2.hpp>

namespace Dunjun
{
struct Rectangle
{
	Rectangle() = default;
	Rectangle(const Rectangle& other) = default;

	Rectangle(f32 x, f32 y, f32 width, f32 height);
	Rectangle(const Vector2& position, const Vector2& size);

	bool contains(const Vector2& point) const;
	bool intersects(const Rectangle& rectangle) const;
	bool intersects(const Rectangle& rectangle, Rectangle& intersection) const;

	f32 x{0};
	f32 y{0};
	f32 width{0};
	f32 height{0};
};

bool operator==(const Rectangle& left, const Rectangle& right);
bool operator!=(const Rectangle& left, const Rectangle& right);

} // namespace Dunjun

#endif
