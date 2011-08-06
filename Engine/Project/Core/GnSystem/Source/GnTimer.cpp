#include "GnSystemPCH.h"
#include "GnTimer.h"

#ifdef WIN32

#else // #ifdef WIN32
#include <sys/time.h>
#endif // #ifdef WIN32

#ifdef WIN32
float GnGetTicks()
{
    // SetThreadAffinityMask \uc2dc\uac04 \ubcf4\uc815\uc5d0 \uad00\ud574\uc11c 
    // \uc5ec\ub7ec\uac1c\uc758 \uc4f0\ub808\ub4dc\uc5d0\uc11c \uc0ac\uc6a9\uc744 \ud558\uac8c \ub418\uba74 \uc774\uc0c1\ud55c \uac12\uc774 \ub4e4\uc5b4 \uc62c \uc218 \uc788\ub2e8\ub2e4.. \ub098\uc911\uc5d0 \ud655\uc778\ud574 \ubcf4\uc790
    // \ud558\uae34 cpu\ub9c8\ub2e4 \ud2f1 \ub3cc\uc544\uac04\uac8c \ub2e4\ub97c \uc218\ub3c4 \uc788\uc73c\ub2c8...
    static bool bFirst = true;
    static LARGE_INTEGER freq;
	static LARGE_INTEGER initial;
    
	if (bFirst)
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&initial);
		bFirst = false;
	}
    
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
    
    now.QuadPart -= initial.QuadPart;
    float tick = (float)((float)now.QuadPart / (float)freq.QuadPart);
	return tick;
}
#elif TARGET_OS_IPHONE // #ifdef WIN32
float GnGetTicks()
{
    static bool bFirst = true;
    static struct timeval start;
    
    if (bFirst)
    {
        gettimeofday(&start, NULL);
        bFirst = false;
    }
    
	struct timeval now;
	gettimeofday(&now, NULL);
    
    __darwin_time_t second = now.tv_sec-start.tv_sec;
    float micro = (float)((float)((float)now.tv_usec-(float)start.tv_usec) / 1000.0f);
    float tick = second + micro;
    return tick;
}
#else // #ifdef WIN32
float GnGetTicks()
{
    static bool bFirst = true;
    static struct timespec start;
    
    if (bFirst)
    {
        clock_gettime(CLOCK_MONOTONIC,&start); 
        bFirst = false;
    }
	
    struct timeval now;
    clock_gettime(CLOCK_MONOTONIC,&now);
	
    __darwin_time_t second = (now.tv_sec-start.tv_sec);
	float micro = (float)((float)now.tv_nsec-(float)start.tv_nsec) / 1000000.0f;
	float tick = second + micro;
    return tick;
}                      
#endif // #ifdef WIN32


GnTimer::GnTimer()
{
	mPerTime = 0.00001f;
    Reset();
}

bool GnTimer::Update(float fPerSec)
{
	mAcumTime += fPerSec;
	if( mAcumTime / mPerTime >= 1.0f )
	{
		Reset();
		return true;
	}
	
	return false;
}
