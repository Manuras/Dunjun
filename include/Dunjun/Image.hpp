#ifndef DUNJUN_IMAGE_HPP
#define DUNJUN_IMAGE_HPP

#include <Dunjun/Types.hpp>

namespace Dunjun
{
class Image
{
public:
	enum Format
	{
		Format_Greyscale = 1,
		Format_GreyscaleAlpha = 2,
		Format_RGB = 3,
		Format_RGBA = 4,
	};

	Image();
	Image(UInt32 width, UInt32 height, Format format,
	      const UInt8* pixels = nullptr);
	Image(const Image& other);
	Image& operator=(const Image& other);
	~Image();

	bool loadFromFile(const char* filename);
	bool loadFromMemory(UInt32 width, UInt32 height, Format format,
	                    const UInt8* pixels);

	inline UInt32 width() const { return m_width; }
	inline UInt32 height() const { return m_height; }
	inline Format format() const { return m_format; }
	inline UInt8* pixelPtr() const { return m_pixels; }

	UInt8* getPixel(UInt32 column, UInt32 row) const;
	void setPixel(UInt32 column, UInt32 row, const UInt32* pixel);

	void flipVertically();
	// void rotate90CCW();

	// void copyRectFromImage(const Image& src,
	//					   UInt32 srcCol, UInt32 srcRow,
	//					   UInt32 destCol, UInt32 destRow,
	//					   UInt32 width, UInt32 height);

	Format m_format;
	UInt32 m_width;
	UInt32 m_height;
	UInt8* m_pixels;
};
} // namespace Dunjun

#endif