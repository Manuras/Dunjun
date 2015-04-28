#ifndef DUNJUN_MATERIAL_HPP
#define DUNJUN_MATERIAL_HPP

#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Texture.hpp>
#include <Dunjun/Color.hpp>

namespace Dunjun
{
struct Material
{
	/* What a final material will look like
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

	ShaderProgram* shaders{nullptr};

	Texture* diffuseMap{nullptr};
	Color diffuseColor{0xFF, 0xFF, 0xFF};

	Color specularColor{0xFF, 0xFF, 0xFF};
	f32 specularExponent{80.0f};
};
} // namespace Dunjun

#endif
