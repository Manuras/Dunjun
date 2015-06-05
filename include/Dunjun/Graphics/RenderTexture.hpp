#ifndef DUNJUN_GRAPHICS_RENDERTEXTURE_HPP
#define DUNJUN_GRAPHICS_RENDERTEXTURE_HPP

#include <Dunjun/System/OpenGL.hpp>
#include <Dunjun/System/Types.hpp>
#include <Dunjun/Graphics/Texture.hpp>

namespace Dunjun
{
class RenderTexture
{
public:
	enum TextureType
	{
		Color = 1,
		Depth = 2,
		ColorAndDepth = Color | Depth,
		Lighting = 4 | Color,
	};

	RenderTexture();

	virtual ~RenderTexture();

	bool create(u32 width,
	            u32 height,
	            TextureType type = ColorAndDepth,
	            TextureFilter minMagFilter = TextureFilter::Linear,
	            TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);

	GLOBAL void bind(const RenderTexture* rt);

	u32 getWidth() const;
	u32 getHeight() const;

	TextureType getType() const;

	u32 getNativeHandle() const;

	// TODO(bill): Specific Method(s) for Textures
	Texture colorTexture;
	Texture depthTexture;

private:
	u32 m_width;
	u32 m_height;

	TextureType m_type;


	u32 m_fbo; // framebuffer
};
} // namespace Dunjun

#endif
