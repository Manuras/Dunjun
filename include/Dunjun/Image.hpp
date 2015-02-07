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
	Image(u32 width, u32 height, Format format, const u8* pixels = nullptr);
	Image(const Image& other);
	Image& operator=(const Image& other);
	~Image();

	bool loadFromFile(const char* filename);
	bool loadFromMemory(u32 width, u32 height, Format format, const u8* pixels);

	inline u32 getWidth() const { return m_width; }
	inline u32 getHeight() const { return m_height; }
	inline Format getFormat() const { return m_format; }
	inline u8* getPixels() const { return m_pixels; }

	u8* getPixel(u32 column, u32 row) const;
	void setPixel(u32 column, u32 row, const u32* pixel);

	void flipVertically();
	// TODO(bill): Implement these methods
	// void rotate90CCW();

	// void copyRectFromImage(const Image& src,
	//					   u32 srcCol, u32 srcRow,
	//					   u32 destCol, u32 destRow,
	//					   u32 width, u32 height);
private:
	Format m_format;
	u32 m_width;
	u32 m_height;
	u8* m_pixels;
};
} // namespace Dunjun

#endif
