#ifndef DUNJUN_IMAGE_HPP
#define DUNJUN_IMAGE_HPP

#include <Dunjun/Types.hpp>

namespace Dunjun
{
enum class ImageFormat
{
	None = 0,
	Greyscale = 1,
	GreyscaleAlpha = 2,
	RGB = 3,
	RGBA = 4,
};

class Image
{
public:
	Image();
	Image(u32 width,
	      u32 height,
	      ImageFormat format,
	      const u8* pixels = nullptr);
	Image(const Image& other);
	Image& operator=(const Image& other);
	~Image();

	bool loadFromFile(const char* filename);
	bool loadFromMemory(u32 width,
	                    u32 height,
	                    ImageFormat format,
	                    const u8* pixels);

	inline u32 getWidth() const { return m_width; }
	inline u32 getHeight() const { return m_height; }
	inline ImageFormat getFormat() const { return m_format; }
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
	ImageFormat m_format;
	u32 m_width;
	u32 m_height;
	u8* m_pixels;
};
} // namespace Dunjun

#endif
