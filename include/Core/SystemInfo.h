
#ifndef _FRAGVIEW_SYSTEMINFO_H_
#define _FRAGVIEW_SYSTEMINFO_H_ 1
#include"../Def.h"

namespace fragview {
/**
 *
 */
	class FVDECLSPEC SystemInfo {
	public:
		enum OperatingSystem {
			eUnix = 0x1,                  /*	*/
			eLinux = (0x2 | eUnix),        /*	*/
			eWindow = 0x4,                  /*	*/
			eFreeBSD = (0x8 | eUnix),        /*	*/
			eMac = (0x10 | eUnix),       /*	*/
			eAndroid = 0x20,                 /*	*/
			eIOS = 0x40,                 /*	*/
			eUnknown = (1 << 31)             /*  */
		};

		enum SIMD {
			eHPM_NONE = (0 << 0),   /*	No HPM SIMD exention flag.	*/
			eHPM_MMX = (1 << 1),   /*	MMX. (Yet not supported)	*/
			eHPM_SSE = (1 << 2),   /*	SSE (Streaming SIMD Extensions).	*/
			eHPM_SSE2 = (1 << 3),   /*	SSE2 (Streaming SIMD Extensions).	*/
			eHPM_SSE3 = (1 << 4),   /*	SSE3 (Streaming SIMD Extensions).	*/
			eHPM_SSSE3 = (1 << 5),   /*	SSSE3 (Streaming SIMD Extensions).	*/
			eHPM_SSE4_1 = (1 << 6),   /*	SSE4.1 (Streaming SIMD Extensions).	*/
			eHPM_SSE4_2 = (1 << 7),   /*	SSE4.2 (Streaming SIMD Extensions).	*/
			eHPM_AVX = (1 << 8),   /*	AVX Version 1 (Advanced Vector Extension).	*/
			eHPM_AVX2 = (1 << 9),   /*	AVX Version 2 (Advanced Vector Extension).	(Not tested)*/
			eHPM_AVX512 = (1 << 10),  /*	AVX512 (Advanced Vector Extension). (Yet not supported)	*/
			eHPM_NEON = (1 << 11),  /*	ARM	FPU (floating-point unit) feature.	*/
		};

		static OperatingSystem getOperatingSystem(void);
		static const char* getOperatingSystemName(OperatingSystem os);

		static SIMD getSupportedSIMD(void);

		static const char *getAppliationName(void);

		static const char *getUserName(void);

		static unsigned int getPageSize(void);

		static unsigned int getCPUCoreCount(void);

		static unsigned int getCPUCacheLine(void);

		static bool supportsVibration(void);

		static unsigned long int systemMemorySize(void);

		//TODO add memory allocation info.
	};
}

#endif