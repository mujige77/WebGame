#ifndef __Core__GnPlatformConfig__
#define __Core__GnPlatformConfig__

#if defined(__GNUC__) && ( defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__MACOS_CLASSIC__) )
#include <TargetConditionals.h>
#endif

#define GNUSE_PLATFORM 0
#define PLATFORM_WIN32 1
#define PLATFORM_IOS 2


#if defined(WIN32)
	#undef GNUSE_PLATFORM
	#define GNUSE_OS PLATFORM_WIN32
	#define GNUSE_PLATFORM PLATFORM_WIN32
#elif defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	#undef GNUSE_PLATFORM
	#define GNUSE_PLATFORM PLATFORM_IOS
#endif


#if !GNUSE_PLATFORM
#error  "Can not recognize the target platform, compling under a unsupported platform?"
#endif 

#endif
