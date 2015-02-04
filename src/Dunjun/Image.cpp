#include <Dunjun/Image.hpp>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

namespace Dunjun
{
Image::Image()
: m_format((Format)0)
, m_width(0)
, m_height(0)
, m_pixels(nullptr)
{
}

Image::Image(UInt32 width, UInt32 height, Format format, const UInt8* pixels)
: m_format((Format)0)
, m_width(0)
, m_height(0)
, m_pixels(nullptr)
{
	loadFromMemory(width, height, format, pixels);
}

Image::Image(const Image& other)
: m_format((Format)0)
, m_width(0)
, m_height(0)
, m_pixels(nullptr)
{
	loadFromMemory(other.m_width, other.m_height, other.m_format, other.m_pixels);
}

Image& Image::operator=(const Image& other)
{
	loadFromMemory(other.m_width, other.m_height, other.m_format, other.m_pixels);
	return *this;
}

Image::~Image()
{
	if (m_pixels)
		delete[] m_pixels;
}

bool Image::loadFromFile(const char* filename)
{
	int width, height, format;
	UInt8* pixels = stbi_load(filename, &width, &height, &format, 0);

	if (!pixels)
	{
		std::cerr << stbi_failure_reason() << std::endl;
		return false;
	}

	loadFromMemory(width, height, (Format)format, pixels);

	stbi_image_free(pixels);

	if (m_pixels)
		return true;
	return false;
}

bool Image::loadFromMemory(UInt32 width, UInt32 height, Format format,
                           const UInt8* pixels)
{
	if (width == 0)
	{
		std::cerr << "Zero width image." << std::endl;
		return false;
	}
	if (height == 0)
	{
		std::cerr << "Zero height image." << std::endl;
		return false;
	}
	if (format <= 0 || format > 4)
	{
		std::cerr << "Invalid texture format." << std::endl;
		return false;
	}

	m_width = width;
	m_height = height;
	m_format = format;

	Size imageSize = width * height * format;

	if (m_pixels)
		delete[] m_pixels;

	m_pixels = new UInt8[imageSize];

	if (pixels != nullptr)
		std::memcpy(m_pixels, pixels, imageSize);

	return true;
}

UInt8* Image::getPixel(UInt32 column, UInt32 row) const
{
	if (column >= m_width || row >= m_height)
		return nullptr;

	return m_pixels + (row * m_width + column) * m_format;
}

void Image::setPixel(UInt32 column, UInt32 row, const UInt32* pixel)
{
	if (column >= m_width || row >= m_height)
		return;

	UInt8* p = getPixel(column, row);
	std::memcpy(p, pixel, m_format);
}

void Image::flipVertically()
{
	Size pitch = m_width * m_format;
	UInt32 halfRows = m_height / 2;
	UInt8* rowBuffer = new UInt8[pitch];

	for (UInt32 i = 0; i < halfRows; i++)
	{
		UInt8* row = m_pixels + (i * m_width) * m_format;
		UInt8* oppositeRow =
		    m_pixels + ((m_height - i - 1) * m_width) * m_format;

		std::memcpy(rowBuffer, row, pitch);
		std::memcpy(row, oppositeRow, pitch);
		std::memcpy(oppositeRow, rowBuffer, pitch);
	}

	delete[] rowBuffer;
}

// void Image::rotate90CCW()
//{

//}

// void Image::copyRectFromImage(const Image& src,
//							  UInt32 srcCol, UInt32 srcRow,
//							  UInt32 destCol, UInt32 destRow,
//							  UInt32 width, UInt32 height)
//{

//}
} // namespace Dunjun