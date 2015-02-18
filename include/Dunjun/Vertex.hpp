#ifndef DUNJUN_VERTEX_HPP
#define DUNJUN_VERTEX_HPP

#include <Dunjun/Math.hpp>
#include <Dunjun/Color.hpp>

namespace Dunjun
{
struct Vertex
{
	Vector3 position;
	Color color;
	Vector2 texCoord;
};
} // namespace Dunjun

#endif 
