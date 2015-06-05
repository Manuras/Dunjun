#ifndef DUNJUN_VIDEOMODE_HPP
#define DUNJUN_VIDEOMODE_HPP

#include <Dunjun/Common.hpp>

#include <vector>

namespace Dunjun
{
struct VideoMode
{
	VideoMode();
	VideoMode(u32 modeWidth, u32 modeHeight, u32 modeBitsPerPixel = 24);

	GLOBAL VideoMode getDesktopMode();
	GLOBAL const std::vector<VideoMode>& getFullscreenModes();

	bool isValid() const;

	u32 width;
	u32 height;
	u32 bitsPerPixel;
};

bool operator==(const VideoMode& left, const VideoMode& right);
bool operator!=(const VideoMode& left, const VideoMode& right);
bool operator<(const VideoMode& left, const VideoMode& right);
bool operator>(const VideoMode& left, const VideoMode& right);
bool operator<=(const VideoMode& left, const VideoMode& right);
bool operator>=(const VideoMode& left, const VideoMode& right);
} // namespace Dunjun

#endif
