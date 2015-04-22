#ifndef DUNJUN_CONFIG_HPP
#define DUNJUN_CONFIG_HPP

// NOTE(bill): Identify the operating system used
// From http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system

#if defined(_WIN32) || defined(_WIN64)
	// Windows
	#define DUNJUN_SYSTEM_WINDOWS

	// Just in case
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

#elif defined(__APPLE__) && defined(__MACH__)
	#define DUNJUN_SYSTEM_OSX

#elif defined(__unix__)
	#define DUNJUN_SYSTEM_UNIX
	// UNIX system, see which one it is
	#if defined(__linux__)
		 // Linux
		#define DUNJUN_SYSTEM_LINUX

	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		// FreeBSD
		#define DUNJUN_SYSTEM_FREEBSD

	#else
		// Unsupported UNIX system
		#error This UNIX operating system is not supported by Dunjun
	#endif

#else
	// Unsupported system
	#error This operating system is not supported by Dunjun
#endif

#include <Dunjun/Types.hpp>

#endif
