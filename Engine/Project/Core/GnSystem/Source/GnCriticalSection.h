#ifndef GNCRITICALSECTION_H
#define GNCRITICALSECTION_H
#include "GnDebug.h"

#define GNMULTITHREADED

class GNSYSTEM_ENTRY GnCriticalSection
{
public:
	GNFORCEINLINE GnCriticalSection();
	GNFORCEINLINE ~GnCriticalSection();
	
	GNFORCEINLINE void Lock();
	GNFORCEINLINE void Unlock();

protected:
#if defined(GNMULTITHREADED)

#if defined(WIN32) || defined(_XENON)
	CRITICAL_SECTION m_kCriticalSection;
#elif defined (_PS3)
	pthread_mutex_t m_kCriticalSection;
#else
	pthread_mutex_t m_kCriticalSection;
#endif // #if defined(WIN32) || defined(_XENON)

#if defined (GNDEBUG)
	bool m_bLocked;
#endif // #if defined (_DEBUG)

#endif // #if defined (NI_MULTITHREADED)
};



GNFORCEINLINE GnCriticalSection::GnCriticalSection()
{
#if defined(GNMULTITHREADED)
#if defined(GNDEBUG)
	m_bLocked = false;
#endif  //#if defined(_DEBUG)

	
#if defined(WIN32) || defined(_XENON)
	InitializeCriticalSection(&m_kCriticalSection);
#else
	pthread_mutex_init(&m_kCriticalSection, NULL);
#endif

#endif // #if !defined(NI_MULTITHREADED)
}

GNFORCEINLINE GnCriticalSection::~GnCriticalSection()
{
#if defined(GNMULTITHREADED)

	#if defined(WIN32) || defined(_XENON)
		DeleteCriticalSection(&m_kCriticalSection);
	#else // defined(WIN32) || defined(_XENON)
		pthread_mutex_destroy(&m_kCriticalSection);
	#endif // defined(WIN32) || defined(_XENON)

#endif // #if !defined(NI_MULTITHREADED)
	
}

GNFORCEINLINE void GnCriticalSection::Lock()
{
#if defined(GNMULTITHREADED)

	#if defined(GNDEBUG)
		GnAssert(m_bLocked == false);
		m_bLocked = true;
	#endif  //#if defined(_DEBUG)

	#if defined(WIN32) || defined(_XENON)
		EnterCriticalSection(&m_kCriticalSection);
	#else // defined(WIN32) || defined(_XENON)
		pthread_mutex_lock(&m_kCriticalSection);
	#endif // defined(WIN32) || defined(_XENON)

#endif // #if !defined(NI_MULTITHREADED)
}

GNFORCEINLINE void GnCriticalSection::Unlock()
{
#if defined(GNMULTITHREADED)

	#if defined(GNDEBUG)
		m_bLocked = false;
	#endif  //#if defined(_DEBUG)

	#if defined(WIN32) || defined(_XENON)
		LeaveCriticalSection(&m_kCriticalSection);
	#else // defined(WIN32) || defined(_XENON)
		pthread_mutex_unlock(&m_kCriticalSection);
	#endif // defined(WIN32) || defined(_XENON)

#endif // #if !defined(NI_MULTITHREADED)
}

#endif // GNCRITICALSECTION_H
