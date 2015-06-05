#ifndef DUNJUN_GRAPHICS_IMAGE_HPP
#define DUNJUN_GRAPHICS_IMAGE_HPP

#include <Dunjun/System/Types.hpp>

#include <string>

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

	bool loadFromFile(const std::string& filename);
	bool loadFromMemory(u32 width,
	                    u32 height,
	                    ImageFormat format,
	                    const u8* pixels);

	const u8* getPixels() const;
	u8* getPixel(u32 column, u32 row) const;
	void setPixel(u32 column, u32 row, const u32* pixel);

	void flipVertically();
	// TODO(bill): Implement these methods
	// void rotate90CCW();

	// void copyRectFromImage(const Image& src,
	//					   u32 srcCol, u32 srcRow,
	//					   u32 destCol, u32 destRow,
	//					   u32 width, u32

	ImageFormat getFormat() const;

	u32 getWidth() const;
	u32 getHeight() const;

private:
	ImageFormat m_format{ImageFormat::None};
	u32 m_width{0};
	u32 m_height{0};
	u8* m_pixels{nullptr};
};
} // namespace Dunjun

#endif
