#ifndef DUNJUN_FILESYSTEM_HPP
#define DUNJUN_FILESYSTEM_HPP

#include <string>

namespace Dunjun
{
namespace FileSystem
{
std::string getBasePath();
std::string getPreferencesPath(const std::string& organization,
							   const std::string& application);
std::string getFileDirectory(const std::string& filepath);
} // namespace FileSystem
} // namespace Dunjun

#endif
