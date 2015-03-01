#ifndef DUNJUN_VERTEX_HPP
#define DUNJUN_VERTEX_HPP

#include <Dunjun/Math.hpp>
#include <Dunjun/Color.hpp>

namespace Dunjun
{
struct Vertex
{
	Vector3 position;
	Vector2 texCoord;
	Color color;
};
} // namespace Dunjun

#endif 
