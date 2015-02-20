#ifndef DUNJUN_TEXTURE_HPP
#define DUNJUN_TEXTURE_HPP

#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Image.hpp>
#include <Dunjun/OpenGL.hpp>

namespace Dunjun
{
class Texture : private NonCopyable
{
public:
	Texture();
	Texture(const Image& image,
	        GLint minMagFilter = GL_LINEAR,
	        GLint wrapMode = GL_CLAMP_TO_EDGE);

	bool loadFromFile(const char* filename,
	                  GLint minMagFilter = GL_LINEAR,
	                  GLint wrapMode = GL_CLAMP_TO_EDGE);
	bool loadFromImage(const Image& image,
	                   GLint minMagFilter = GL_LINEAR,
	                   GLint wrapMode = GL_CLAMP_TO_EDGE);

	virtual ~Texture();

	void bind(GLuint position) const;

	ReadOnly<GLuint, Texture> object;
	ReadOnly<GLsizei, Texture> width;
	ReadOnly<GLsizei, Texture> height;
};
} // namespace Dunjun

#endif
