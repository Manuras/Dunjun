#ifndef DUNJUN_GRAPHICS_MATERIAL_HPP
#define DUNJUN_GRAPHICS_MATERIAL_HPP

#include <Dunjun/Graphics/ShaderProgram.hpp>
#include <Dunjun/Graphics/Texture.hpp>
#include <Dunjun/Graphics/Color.hpp>

namespace Dunjun
{
struct Material
{
	/*
	  What a final material will look like
	    shaders

	    diffuse / albedo
	    - map
	    - color

	    specular
	    - map
	    - color
	    - exponent / smoothness


	    // Other things

	    ambient occlusion
	    - map

	    emissive
	    - map

	    detail
	    - map
	    - color
	 */


	// TODO(bill): Restrict types/number of shaders and use an enum rather
	// than a pointer?
	ShaderProgram* shaders{nullptr};

	Texture* diffuseMap{nullptr};
	Color diffuseColor{0xFF, 0xFF, 0xFF};

	Color specularColor{0xFF, 0xFF, 0xFF};
	f32 specularExponent{80.0f};
};
} // namespace Dunjun

#endif
