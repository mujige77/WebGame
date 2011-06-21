#include "GnSystemPCH.h"
#include "GnMemoryManager.h"
#include "GnDebugAllocator.h"
#include "GnStandardAllocator.h"

GnMemoryManager* GnMemoryManager::msMemManager = 0;


bool GnMemoryManager::IsInitialized()
{
	return msMemManager != 0;
}

void GnMemoryManager::EBMStartup()
{
	msMemManager = GnExternalNew GnMemoryManager();
#ifdef GN_MEMORY_DEBUGGER
	msMemManager->mAllocator = GnExternalNew GnDebugAllocator(GnExternalNew GnStandardAllocator());
#else // #ifdef GN_MEMORY_DEBUGGER
	msMemManager->mAllocator = GnExternalNew GnStandardAllocator();
#endif // #ifdef GN_MEMORY_DEBUGGER
	msMemManager->mAllocator->Initialize();
}

void GnMemoryManager::EBMShutdown()
{
	GnAssert(msMemManager->mAllocator);

	msMemManager->mAllocator->Shutdown(); 
	GnExternalDelete msMemManager->mAllocator;
	GnExternalDelete msMemManager;
	msMemManager = NULL;
}

bool GnMemoryManager::VerifyAddress(const void* pvMemory)
{
	GnAssert(msMemManager->mAllocator);
#ifdef GN_MEMORY_DEBUGGER
	return msMemManager->mAllocator->VerifyAddress(pvMemory);
#else
	return true;
#endif
}

GnMemoryManager* GnMemoryManager::Instance()
{
	return msMemManager;
}

void* GnMemoryManager::Allocate(gsize stSizeInBytes, gsize stAlignment,
    GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate,
    const char *pcSourceFile, int iSourceLine, const char* pcFunction)
{
	GnAssert(mAllocator);
    
	void* pvMem = ALLOCTOR_ALLOCATE(stSizeInBytes, stAlignment, eEventType, bProvideAccurateSizeOnDeallocate, 
		pcSourceFile, iSourceLine, pcFunction);
    
	return pvMem;
}

void* GnMemoryManager::Reallocate(void* pvMem, gsize stSizeInBytes, 
    gsize stAlignment, GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate,
    gsize stSizeCurrent, const char *pcSourceFile, int iSourceLine, const char* pcFunction)
{
	GnAssert(mAllocator);
    
	void* pvNewMem = ALLOCTOR_REALLOCATE(pvMem, stSizeInBytes, stAlignment, eEventType,
		bProvideAccurateSizeOnDeallocate, stSizeCurrent, pcSourceFile, iSourceLine, pcFunction);
	return pvNewMem;
}

void GnMemoryManager::Deallocate(void* pvMem,
	GnMemoryEventType eEventType, gsize stSizeinBytes)
{
	GnAssert(mAllocator);
    
	mAllocator->Deallocate(pvMem, eEventType, stSizeinBytes);    
}

bool GnMemoryManager::TrackAllocate(const void* const pvMem, gsize stSizeInBytes
	, GnMemoryEventType eEventType, const char *pcSourceFile, int iSourceLine, const char* pcFunction)
{
	GnAssert(mAllocator);
    
#ifdef GN_MEMORY_DEBUGGER
	return mAllocator->TrackAllocate(pvMem, stSizeInBytes, eEventType, pcSourceFile, iSourceLine
		, pcFunction);
#else
	return false;
#endif	
}

bool GnMemoryManager::TrackDeallocate(const void* const pvMem, GnMemoryEventType eEventType)
{
	GnAssert(mAllocator);
    
#ifdef GN_MEMORY_DEBUGGER
	return mAllocator->TrackDeallocate(pvMem, eEventType);
#else
	return false;
#endif
	
}

const char* GnMemoryManager::GnMemoryEventTypeToString(GnMemoryEventType eEventType)
{
	switch (eEventType)
	{
        case GN_UNKNOWN:
            return "GN_UNKNOWN";
        case GN_OPER_NEW:
            return "GN_OPER_NEW";
        case GN_OPER_NEW_ARRAY:
            return "GN_OPER_NEW_ARRAY";
        case GN_OPER_DELETE:
            return "GN_OPER_DELETE";
        case GN_OPER_DELETE_ARRAY:
            return "GN_OPER_DELETE_ARRAY";
        case GN_MALLOC:
            return "GN_MALLOC";
        case GN_REALLOC:
            return "GN_REALLOC";
        case GN_ALIGNEDMALLOC:
            return "GN_ALIGNEDMALLOC";
        case GN_ALIGNEDREALLOC:
            return "GN_ALIGNEDREALLOC";
        case GN_FREE:
            return "GN_FREE";
        case GN_ALIGNEDFREE:
            return "GN_ALIGNEDFREE";
        case GN_EXTERNALALLOC:
            return "GN_EXTERNALALLOC";
        case GN_EXTERNALFREE:
            return "GN_EXTERNALFREE";
        default:
            GnAssert(!"Unknown GnMemoryEventType  value!");
	};
    
	return NULL;
}

