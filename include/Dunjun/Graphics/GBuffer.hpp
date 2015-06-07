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
	enum TextureType
	{
		Diffuse, // TODO(bill): Rename to albedo? (PBR Shaders...)
 		Specular,
		Normal,
		Depth,
		// TODO(bill): Emission,
		Count,
	};

	GBuffer();
	virtual ~GBuffer();

	bool create(u32 width, u32 height);

	GLOBAL void bind(const GBuffer* b);

	u32 getWidth() const;
	u32 getHeight() const;

	u32 getNativeHandle() const;

	const Texture& getTexture(TextureType type) const;

private:
	u32 m_width;
	u32 m_height;

	u32 m_fbo;

	Texture m_textures[TextureType::Count];
};
} // namespace Dunjun

#endif
