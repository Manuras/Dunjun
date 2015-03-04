#ifndef DUNJUN_TEXTURE_HPP
#define DUNJUN_TEXTURE_HPP

#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Image.hpp>
#include <Dunjun/OpenGL.hpp>

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

	bool loadFromFile(const char* filename,
	                  TextureFilter minMagFilter = TextureFilter::Linear,
	                  TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);
	bool loadFromImage(const Image& image,
	                   TextureFilter minMagFilter = TextureFilter::Linear,
	                   TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);

	virtual ~Texture();

	void bind(GLuint position) const;

	ReadOnly<GLuint, Texture> object;
	ReadOnly<GLsizei, Texture> width;
	ReadOnly<GLsizei, Texture> height;
};
} // namespace Dunjun

#endif
