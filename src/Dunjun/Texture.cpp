#include <Dunjun/Texture.hpp>

#include <Dunjun/Common.hpp>

namespace Dunjun
{
INTERNAL GLenum getInteralFormat(Image::Format format, bool srgb)
{
	switch (format)
	{
	case Image::Format_Greyscale:
		return GL_LUMINANCE;
	case Image::Format_GreyscaleAlpha:
		return GL_LUMINANCE_ALPHA;
	case Image::Format_RGB:
		return (srgb ? GL_SRGB : GL_RGB);
	case Image::Format_RGBA:
		return (srgb ? GL_SRGB_ALPHA : GL_RGBA);
	}
}

Texture::Texture()
: m_object(0)
, m_width(0)
, m_height(0)
{
	glGenTextures(1, &m_object);
}

Texture::Texture(const Image& image, GLint minMagFilter, GLint wrapMode)
: m_object(0)
, m_width(image.getWidth())
, m_height(image.getHeight())
{
	glGenTextures(1, &m_object);

	if (!loadFromImage(image, minMagFilter, wrapMode))
		throw std::runtime_error("Could not create texture from image.");
}

bool Texture::loadFromFile(const char* filename, GLint minMagFilter,
                           GLint wrapMode)
{
	Image image;
	if (!image.loadFromFile(filename))
		return false;
	image.flipVertically();

	return loadFromImage(image, minMagFilter, wrapMode);
}

bool Texture::loadFromImage(const Image& image, GLint minMagFilter,
                            GLint wrapMode)
{
	if (image.getFormat() <= 0 || image.getFormat() > 4)
		return false;

	m_width = (GLfloat)image.getWidth();
	m_height = (GLfloat)image.getHeight();

	glGenTextures(1, &m_object);
	glBindTexture(GL_TEXTURE_2D, m_object);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, getInteralFormat(image.getFormat(), true),
	             (GLsizei)m_width, (GLsizei)m_height, 0,
	             getInteralFormat(image.getFormat(), false), GL_UNSIGNED_BYTE,
	             image.getPixelPtr());

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

Texture::~Texture() { glDeleteTextures(1, &m_object); }

void Texture::bind(GLuint position)
{
	if (position > 31)
	{
		std::cerr << "Textures can only be bount to position [0 ... 31]\n";
		std::cerr << "Will bind to position [31]" << std::endl;
		position = 31;
	}

	glActiveTexture(GL_TEXTURE0 + position);
	glClientActiveTexture(GL_TEXTURE0 + position);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, (m_object ? m_object : 0));
	glDisable(GL_TEXTURE_2D);
}

} // namespace Dunjun