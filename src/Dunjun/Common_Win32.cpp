#include <Dunjun/Config.hpp>
#ifdef DUNJUN_SYSTEM_WINDOWS
#include <Dunjun/Common.hpp>

#include <Windows.h>

namespace Dunjun
{
std::string resourcePath()
{
	char executablePath[1024]{'\0'};
	DWORD charsCopied{GetModuleFileName(nullptr, (LPWSTR)executablePath, 1024)};
	if (charsCopied > 0 && charsCopied < 1024)
		return std::string{executablePath} + std::string{"\\..\\"};
	return {""};
}
} // namespace Dunjun
#endif
