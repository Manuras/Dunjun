#ifndef DUNJUN_MATERIAL_HPP
#define DUNJUN_MATERIAL_HPP

#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Texture.hpp>

namespace Dunjun
{
struct Material
{
	ShaderProgram* shaders;
	Texture* texture;
};
} // namespace Dunjun

#endif
