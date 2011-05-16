#include "GnSystemPCH.h"
#include "GnMemoryDefine.h"
#include "GnMemoryManager.h"

#ifdef GN_MEMORY_DEBUGGER
void* _GnMalloc(gsize stSizeInBytes, const char* pcSourceFile,int iSourceLine,
	const char* pcFunction)
#else
void* _GnMalloc(gsize stSizeInBytes)
#endif
{
	if (stSizeInBytes == 0)
		stSizeInBytes = 1;

	return GnMemoryManager::Instance()->Allocate(stSizeInBytes, GN_MEM_ALIGNMENT,
				GN_MALLOC, false
		#ifdef GN_MEMORY_DEBUGGER
				, pcSourceFile, iSourceLine, pcFunction
		#endif
		);
}


#ifdef GN_MEMORY_DEBUGGER
void* _GnAlignedMalloc(gsize stSizeInBytes, gsize stAlignment, const char* pcSourceFile, 
   int iSourceLine, const char* pcFunction)
#else // #ifdef GN_MEMORY_DEBUGGER
void* _GnAlignedMalloc(gsize stSizeInBytes, gsize stAlignment)
#endif // #ifdef GN_MEMORY_DEBUGGER
{
	if (stSizeInBytes == 0)
		stSizeInBytes = 1;

	return GnMemoryManager::Instance()->Allocate(stSizeInBytes, stAlignment,
		GN_MALLOC, false
#ifdef GN_MEMORY_DEBUGGER
		, pcSourceFile, iSourceLine, pcFunction
#endif
		);
}


#ifdef GN_MEMORY_DEBUGGER
void* _GnRealloc(void *pvMem, gsize stSizeInBytes, const char* pcSourceFile,
	int iSourceLine, const char* pcFunction)
#else
void* _GnRealloc(void *pvMem, gsize stSizeInBytes)
#endif
{
	if (stSizeInBytes == 0 && pvMem != 0)
	{
		GnFree(pvMem);
		return NULL;
	}
	else if (pvMem == 0)
	{
		return _GnMalloc(stSizeInBytes
#ifdef GN_MEMORY_DEBUGGER
			, pcSourceFile, iSourceLine, pcFunction
#endif
			);
	}

	// Actually reallocate the memory
	pvMem = GnMemoryManager::Instance()->Reallocate(pvMem, stSizeInBytes, 
		GN_MEM_ALIGNMENT, GN_REALLOC, false, GN_MEM_DEALLOC_SIZE_DEFAULT
#ifdef GN_MEMORY_DEBUGGER
		, pcSourceFile, iSourceLine, pcFunction
#endif
		);

	return pvMem; 
}


#ifdef GN_MEMORY_DEBUGGER
void* _GnAlignedRealloc(void *pvMem, gsize stSizeInBytes, gsize stAlignment, 
	const char* pcSourceFile, int iSourceLine, const char* pcFunction)
#else // #ifdef GN_MEMORY_DEBUGGER
void* _GnAlignedRealloc(void *pvMem, gsize stSizeInBytes, gsize stAlignment)
#endif // #ifdef GN_MEMORY_DEBUGGER
{
	GnAssert(GnMemoryManager::IsInitialized());

	// If the intention is to use GnRealloc like GnFree, just use
	// GnFree.
	if (stSizeInBytes == 0 && pvMem != 0)
	{
		GnAlignedFree(pvMem);
		return NULL;
	}
	else if (pvMem == 0)
	{
		return _GnAlignedMalloc(stSizeInBytes, stAlignment
#ifdef GN_MEMORY_DEBUGGER
			, pcSourceFile, iSourceLine, pcFunction
#endif
			);
	}

	// Actually reallocate the memory
	return GnMemoryManager::Instance()->Reallocate(pvMem, stSizeInBytes, 
		stAlignment, GN_ALIGNEDREALLOC, false, GN_MEM_DEALLOC_SIZE_DEFAULT
#ifdef GN_MEMORY_DEBUGGER
		, pcSourceFile, iSourceLine, pcFunction
#endif
		);
}

void _GnFree(void* pvMem)
{
	if (pvMem == NULL)
		return;

	GnMemoryManager::Instance()->Deallocate(pvMem,GN_FREE);
}

void _GnAlignedFree(void* pvMem)
{
	if (pvMem == NULL)
		return;

	GnMemoryManager::Instance()->Deallocate(pvMem, GN_ALIGNEDFREE);
}

#ifdef GN_MEMORY_DEBUGGER
int  GnVerifyAddress(const void* pvMemory)
{
	if (pvMemory == NULL)
		return true;

	GnAssert(GnMemoryManager::IsInitialized());
	return (int)GnMemoryManager::Instance()->VerifyAddress(pvMemory);
}
#endif

void GnMeomeyAssert(const char* pcCondition, /*GnAllocUnit* pkUnit, */
					 const char* pcFile, int iLine, const char* pcFunction)
{
	//GnAssert(msGnAssertFunc);
	//GnDebug::msGnAssertFunc(pcCondition, pcFile, pcFunction, iLine);
	//NILOG("%s:%d (%s) %s -- GnMemAssert failed.\n", pcFile, iLine, pcFunction, pcCondition);
	//if (pkUnit)
	//{
	//	GnAssert(GnMemTracker::Get());
	//	GnMemTracker::Get()->LogAllocUnit(pkUnit, NIMESSAGE_GENERAL_0);
	//}
}