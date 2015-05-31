#include <Dunjun/Config.hpp>
#ifdef DUNJUN_SYSTEM_OSX
#include <Dunjun/Common.hpp>

#include <CoreFoundation/CoreFoundation.h>

namespace Dunjun
{
std::string resourcePath()
{
	CFBundleRef mainBundle{CFBundleGetMainBundle()};
	CFURLRef resourcesURL{CFBundleCopyResourcesDirectoryURL(mainBundle)};
	char path[PATH_MAX];
	if (!CFURLGetFileSystemRepresentation(
	        resourcesURL, TRUE, (UInt8*)path, PATH_MAX))
	{
		// POSIX
		char executablePath[FILENAME_MAX]{0};
		if (!getcwd(executablePath, sizeof(executablePath)))
			return "";

		// not really required
		executablePath[sizeof(executablePath) - 1] = '\0';

		return std::string{executablePath} + "/";
	}
	CFRelease(resourcesURL);

	return std::string{path} + "/";
}
} // namespace Dunjun
#endif
