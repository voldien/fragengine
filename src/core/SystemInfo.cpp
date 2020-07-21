#include <SDL2/SDL_platform.h>
#include <SDL2/SDL_cpuinfo.h>
#include"Core/SystemInfo.h"
#include<hpm/hpm.h>
#include <Exception/InvalidArgumentException.h>

using namespace fragview;

SystemInfo::OperatingSystem SystemInfo::getOperatingSystem(void) {
	/*  */
	const char *os = SDL_GetPlatform();

	/*  */
	if (strcmp(os, "Linux") == 0)
		return SystemInfo::Linux;
	if (strcmp(os, "Windows") == 0)
		return SystemInfo::Window;
	if (strcmp(os, "Android") == 0)
		return SystemInfo::Android;
	if (strcmp(os, "unix") == 0)
		return SystemInfo::Unix;
	if (strcmp(os, "iOS") == 0)
		return SystemInfo::IOS;
	if (strcmp(os, "Mac OS X") == 0)
		return SystemInfo::Mac;

	return SystemInfo::Unknown;
}

const char *SystemInfo::getOperatingSystemName(SystemInfo::OperatingSystem os) {

	/*  */
	switch (os) {
		case SystemInfo::Linux:
			return "Linux";
		case SystemInfo::Window:
			return "Window";
		case SystemInfo::Unix:
			return "Unix";
		case SystemInfo::Android:
			return "Android";
		case SystemInfo::Mac:
			return "Mac";
		case SystemInfo::IOS:
			return "IOS";
		case SystemInfo::FreeBSD:
			return "FreeBSD";
		default:
			throw InvalidArgumentException("Invalid Operating System Enumerator");
	}
}

SystemInfo::SIMD SystemInfo::getSupportedSIMD(void) {
	SystemInfo::SIMD supportedSIMD = HPM_NONE;

	for (int i = 1; i < 11; i++) {
		if (hpm_support_cpu_feat(1 << i))
			supportedSIMD |= (SystemInfo::SIMD) (1 << i);
	}
	return supportedSIMD;
}

const char *SystemInfo::getAppliationName(void) {
#   if defined(FV_GNUC) || defined(FV_UNIX)
//	extern char* __progname;
//	return __progname;
#else
	return NULL;
#endif
}

const char *SystemInfo::getUserName(void) {
	return "";
}

unsigned int SystemInfo::getPageSize(void) {
	return 1024;
}

unsigned int SystemInfo::getCPUCoreCount(void) {
	return SDL_GetCPUCount();
}

unsigned int SystemInfo::getCPUCacheLine(void) {
	return SDL_GetCPUCacheLineSize();
}

bool SystemInfo::supportsVibration(void) {
	return false;
}

unsigned long int SystemInfo::systemMemorySize(void) {
	return SDL_GetSystemRAM();
}
