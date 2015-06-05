#ifndef DUNJUN_CONTEXTSETTINGS_HPP
#define DUNJUN_CONTEXTSETTINGS_HPP

#include <Dunjun/Common.hpp>

namespace Dunjun
{
struct ContextSettings
{
	explicit ContextSettings(u32 depthBits = 0,
	                         u32 stencilBits = 0,
	                         u32 antialiasingLevel = 0,
	                         u32 majorVersion = 2,
	                         u32 minorVersion = 1)
	: depthBits{depthBits}
	, stencilBits{stencilBits}
	, antialiasingLevel{antialiasingLevel}
	, majorVersion{majorVersion}
	, minorVersion{minorVersion}
	{
	}

	u32 depthBits{0};
	u32 stencilBits{0};
	u32 antialiasingLevel{0}; // TODO(bill): We are using Deferred Shading
	                          // show this could be number of passes
	u32 majorVersion{2};
	u32 minorVersion{1};

	// TODO(bill): Anisotropic?
};
} // namespace Dunjun

#endif
