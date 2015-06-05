#ifndef DUNJUN_GRAPHICS_GBUFFER_HPP
#define DUNJUN_GRAPHICS_GBUFFER_HPP

#include <Dunjun/System/OpenGL.hpp>
#include <Dunjun/System/Types.hpp>
#include <Dunjun/Graphics/Texture.hpp>

namespace Dunjun
{
class GBuffer
{
public:
	GBuffer();
	virtual ~GBuffer();

	bool create(u32 width, u32 height);

	GLOBAL void bind(const GBuffer* b);

	u32 getWidth() const;
	u32 getHeight() const;

	u32 getNativeHandle() const;

	// TODO(bill): Specific Method(s) for texture retrieval ???

	Texture diffuse;  // diffuse color (rgb)
	Texture specular; // specular color (rgb), smootness (a)
	Texture normal;   // world normal (rgb)
	// TODO(bill): emission RT
	// Texture emission;
	Texture depth;

private:
	u32 m_width;
	u32 m_height;

	u32 m_fbo;
};
} // namespace Dunjun

#endif
