#include <Dunjun/Math/Rectangle.hpp>

// TODO(bill): implement math functions
#include <algorithm>

namespace Dunjun
{
Rectangle::Rectangle(f32 x, f32 y, f32 width, f32 height)
: x(x)
, y(y)
, width(width)
, height(height)
{
}
Rectangle::Rectangle(const Vector2& position, const Vector2& size)
: x(position.x)
, y(position.y)
, width(size.x)
, height(size.y)
{
}

bool Rectangle::contains(const Vector2& point) const
{
	// TODO(bill): compare similar due to floating point arithmetic
	f32 minX = std::min(x, x + width);
	f32 maxX = std::max(x, x + width);
	f32 minY = std::min(y, y + height);
	f32 maxY = std::max(y, y + height);

	return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) &&
	       (point.y < maxY);
}

bool Rectangle::intersects(const Rectangle& rectangle) const
{
	Rectangle intersection;
	return intersects(rectangle, intersection);
}

bool Rectangle::intersects(const Rectangle& rectangle,
                           Rectangle& intersection) const
{
	f32 r1MinX = std::min(x, x + width);
	f32 r1MaxX = std::max(x, x + width);
	f32 r1MinY = std::min(y, y + height);
	f32 r1MaxY = std::max(y, y + height);

	f32 r2MinX = std::min(rectangle.x, rectangle.x + rectangle.width);
	f32 r2MaxX = std::max(rectangle.x, rectangle.x + rectangle.width);
	f32 r2MinY = std::min(rectangle.y, rectangle.y + rectangle.height);
	f32 r2MaxY = std::max(rectangle.y, rectangle.y + rectangle.height);

	f32 x1 = std::max(r1MinX, r2MinX);
	f32 x2 = std::min(r1MaxX, r2MaxX);

	f32 y1 = std::max(r1MinY, r2MinY);
	f32 y2 = std::min(r1MaxY, r2MaxY);

	// If intersection is valid (positive non-zero area)
	if ((x1 < x2) && (y1 < y2))
	{
		intersection = Rectangle(x1, y1, x2 - x1, y2 - y1);
		return true;
	}
	else
	{
		intersection = Rectangle(0, 0, 0, 0);
		return false;
	}
}

bool operator==(const Rectangle& left, const Rectangle& right)
{
	// TODO(bill): compare similar due to floating point arithmetic
	return (left.x == right.x) && (left.y == right.y) &&
	       (left.width == right.width) && (left.height == right.height);
}

bool operator!=(const Rectangle& left, const Rectangle& right)
{
	return !(left == right);
}

} // namespace Dunjun
