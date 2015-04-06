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

class RenderTexture;

class Texture : private NonCopyable
{
public:
	Texture();
	Texture(const Image& image,
	        TextureFilter minMagFilter = TextureFilter::Linear,
	        TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);

	bool loadFromFile(const char* filename,
	                  TextureFilter minMagFilter = TextureFilter::Linear,
	                  TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);
	bool loadFromImage(const Image& image,
	                   TextureFilter minMagFilter = TextureFilter::Linear,
	                   TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);

	virtual ~Texture();

	GLOBAL void bind(const Texture* tex, GLuint position);

	GLsizei width;
	GLsizei height;

private:
	friend class RenderTexture;

	GLuint m_object;
};
} // namespace Dunjun

#endif
