#ifndef DUNJUN_RESOURCEHOLDERS_HPP
#define DUNJUN_RESOURCEHOLDERS_HPP

#include <Dunjun/ResourceHolder.hpp>
#include <Dunjun/Texture.hpp>
#include <Dunjun/ShaderProgram.hpp>

namespace Dunjun
{
using TextureHolder = ResourceHolder<Texture, std::string>;
using ShaderHolder = ResourceHolder<ShaderProgram, std::string>;

extern TextureHolder g_textureHolder;
extern ShaderHolder g_shaderHolder;
} // namespace Dunjun

#endif
