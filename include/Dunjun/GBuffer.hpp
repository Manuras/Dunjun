#ifndef DUNJUN_GBUFFER_HPP
#define DUNJUN_GBUFFER_HPP

#include <Dunjun/OpenGL.hpp>
#include <Dunjun/Types.hpp>
#include <Dunjun/Texture.hpp>

namespace Dunjun
{
class GBuffer
{
public:
	GBuffer();
	virtual ~GBuffer();

	bool create(u32 width, u32 height);

	GLOBAL void bind(const GBuffer* b);
	GLOBAL void unbind(const GBuffer* b);

	ReadOnly<u32, GBuffer> width;
	ReadOnly<u32, GBuffer> height;

	ReadOnly<GLuint, GBuffer> fbo;

	Texture diffuse;  // diffuse color (rgb)
	Texture specular; // specular color (rgb), smootness (a)
	Texture normal;    // world normal (rgb)
	// TODO(bill): emission RT
	// Texture emission;
	Texture depth;
};
} // namespace Dunjun

#endif
