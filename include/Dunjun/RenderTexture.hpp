#ifndef DUNJUN_RENDERTEXTURE_HPP
#define DUNJUN_RENDERTEXTURE_HPP

#include <Dunjun/OpenGL.hpp>
#include <Dunjun/Types.hpp>
#include <Dunjun/Texture.hpp>

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
	};

	RenderTexture();
	virtual ~RenderTexture();

	bool create(u32 width,
	            u32 height,
	            TextureType type = ColorAndDepth,
	            TextureFilter minMagFilter = TextureFilter::Linear,
	            TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);

	GLOBAL void bind(const RenderTexture* rt);
	GLOBAL void unbind(const RenderTexture* rt);

	ReadOnly<u32, RenderTexture> width;
	ReadOnly<u32, RenderTexture> height;

	ReadOnly<TextureType, RenderTexture> type;

	Texture colorTexture;
	Texture depthTexture;
	ReadOnly<GLuint, RenderTexture> fbo; // framebuffer
};
} // namespace Dunjun

#endif
