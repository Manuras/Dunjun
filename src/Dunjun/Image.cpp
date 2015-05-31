#include <Dunjun/Image.hpp>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <cstring>

namespace Dunjun
{
Image::Image()
: m_format{ImageFormat::None}
, m_width{0}
, m_height{0}
, m_pixels{nullptr}
{
}

Image::Image(u32 w, u32 h, ImageFormat f, const u8* p)
: m_format{ImageFormat::None}
, m_width{0}
, m_height{0}
, m_pixels{nullptr}
{
	loadFromMemory(w, h, f, p);
}

Image::Image(const Image& other)
: m_format{ImageFormat::None}
, m_width{0}
, m_height{0}
, m_pixels{nullptr}
{
	loadFromMemory(
	    other.m_width, other.m_height, other.m_format, other.m_pixels);
}

Image& Image::operator=(const Image& other)
{
	loadFromMemory(
	    other.m_width, other.m_height, other.m_format, other.m_pixels);
	return *this;
}

Image::~Image()
{
	if (m_pixels)
		delete[] m_pixels;
}

bool Image::loadFromFile(const std::string& filename)
{
	int w, h, f;
	u8* p{stbi_load(filename.c_str(), &w, &h, &f, 0)};

	if (!p)
	{
		std::cerr << stbi_failure_reason() << std::endl;
		return false;
	}

	loadFromMemory(w, h, (ImageFormat)f, p);

	stbi_image_free(p);

	if (m_pixels)
		return true;
	return false;
}

bool Image::loadFromMemory(u32 w, u32 h, ImageFormat f, const u8* p)
{
	if (w == 0)
	{
		std::cerr << "Zero width image." << std::endl;
		return false;
	}
	if (h == 0)
	{
		std::cerr << "Zero height image." << std::endl;
		return false;
	}

	m_width = w;
	m_height = h;
	m_format = f;

	usize imageSize{m_width * m_height * (usize)f};

	if (m_pixels)
		delete[] m_pixels;

	m_pixels = new u8[imageSize];

	if (p != nullptr)
		std::memcpy(m_pixels, p, imageSize);

	return true;
}

const u8* Image::getPixels() const { return m_pixels; }

u8* Image::getPixel(u32 column, u32 row) const
{
	if (column >= m_width || row >= m_height)
		return nullptr;

	return m_pixels + (row * m_width + column) * (usize)m_format;
}

void Image::setPixel(u32 column, u32 row, const u32* pixel)
{
	if (column >= m_width || row >= m_height)
		return;

	u8* p{getPixel(column, row)};
	std::memcpy(p, pixel, (usize)m_format);
}

void Image::flipVertically()
{
	usize pitch{m_width * (usize)m_format};
	u32 halfRows{m_height / 2};
	u8* rowBuffer{new u8[pitch]};

	for (u32 i{0}; i < halfRows; i++)
	{
		u8* row{m_pixels + (i * m_width) * (usize)m_format};
		u8* oppositeRow{m_pixels +
		                ((m_height - i - 1) * m_width) * (usize)m_format};

		std::memcpy(rowBuffer, row, pitch);
		std::memcpy(row, oppositeRow, pitch);
		std::memcpy(oppositeRow, rowBuffer, pitch);
	}

	delete[] rowBuffer;
}

ImageFormat Image::getFormat() const { return m_format; }

u32 Image::getWidth() const { return m_width; }
u32 Image::getHeight() const { return m_height; }

// void Image::rotate90CCW()
//{

//}

// void Image::copyRectFromImage(const Image& src,
//							  u32 srcCol, u32 srcRow,
//							  u32 destCol, u32 destRow,
//							  u32 width, u32 height)
//{

//}
} // namespace Dunjun
