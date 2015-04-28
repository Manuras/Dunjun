#ifndef DUNJUN_TEXTURE_HPP
#define DUNJUN_TEXTURE_HPP

#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Image.hpp>
#include <Dunjun/OpenGL.hpp>
#include <Dunjun/Common.hpp>

namespace Dunjun
{
enum class TextureFilter : GLint
{
	Linear = GL_LINEAR,
	Nearest = GL_NEAREST,
};

enum class TextureWrapMode : GLint
{
	Clamp = GL_CLAMP,
	Repeat = GL_REPEAT,
	ClampToEdge = GL_CLAMP_TO_EDGE,
	ClampToBorder = GL_CLAMP_TO_BORDER,
	MirroredRepeat = GL_MIRRORED_REPEAT,
};

class Texture : private NonCopyable
{
public:
	Texture();
	Texture(const Image& image,
	        TextureFilter minMagFilter = TextureFilter::Linear,
	        TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);

	bool loadFromFile(const std::string& filename,
	                  TextureFilter minMagFilter = TextureFilter::Linear,
	                  TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);
	bool loadFromImage(const Image& image,
	                   TextureFilter minMagFilter = TextureFilter::Linear,
	                   TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);

	virtual ~Texture();

	GLOBAL void bind(const Texture* tex, GLuint position);

	s32 getWidth() const;
	s32 getHeight() const;

	GLuint getNativeHandle() const;

private:
	friend class RenderTexture;
	friend class GBuffer;

	s32 m_width;
	s32 m_height;

	GLuint m_object;
};
} // namespace Dunjun

#endif
