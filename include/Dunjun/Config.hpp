#ifndef DUNJUN_CONFIG_HPP
#define DUNJUN_CONFIG_HPP

#if defined(_WIN32)
	// Windows
	#define DUNJUN_SYSTEM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

#elif defined(__APPLE__)
	#define DUNJUN_SYSTEM_OSX

#elif defined(__unix__)
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

#endif
