#ifndef GNMEMORYMANAGER_H
#define GNMEMORYMANAGER_H
#include "GnAllocator.h"


class GNSYSTEM_ENTRY GnMemoryManager
{
public:
	static void EBMStartup();
	static void EBMShutdown();
	static GnMemoryManager* Instance();
	static bool IsInitialized();

	// 3 funnel points for all memory operations:
	void* Allocate(gsize stSize, gsize stAlignment, GnMemoryEventType eEventType,
		bool bProvideAccurateSizeOnDeallocate = false,
		const char *pcSourceFile = GN_MEM_FILE_DEFAULT,
		int iSourceLine = GN_MEM_LINE_DEFAULT,
		const char* pcFunction = GN_MEM_FUNCTION_DEFAULT
		);

	void* Reallocate(void* pvMem, gsize stSize, gsize stAlignment,
		GnMemoryEventType eEventType,
		bool bProvideAccurateSizeOnDeallocate = false,
		gsize stSizeCurrent = GN_MEM_DEALLOC_SIZE_DEFAULT,
		const char *pcSourceFile = GN_MEM_FILE_DEFAULT,
		int iSourceLine = GN_MEM_LINE_DEFAULT,
		const char* pcFunction = GN_MEM_FUNCTION_DEFAULT
		);

    void Deallocate(void* pvMem, GnMemoryEventType eEventType,
		gsize stSizeinBytes= GN_MEM_DEALLOC_SIZE_DEFAULT);

	bool TrackAllocate(const void* const pvMemory, gsize stSizeInBytes,
		GnMemoryEventType eEventType,
		const char *pcSourceFile = GN_MEM_FILE_DEFAULT,
		int iSourceLine = GN_MEM_LINE_DEFAULT,
		const char* pcFunction = GN_MEM_FUNCTION_DEFAULT
		);

	bool TrackDeallocate(const void* const pvMemory, GnMemoryEventType eEventType);

	static bool VerifyAddress(const void* pvMemory);

	// Utility functions
	static const char* GnMemoryEventTypeToString(GnMemoryEventType eEventType);

protected:
	GnMemoryManager() {};
	GnMemoryManager(const GnMemoryManager&) {};

	static GnMemoryManager* msMemManager;
	GnAllocator* mAllocator;
};

#ifdef GN_MEMORY_DEBUGGER

#define ALLOCTOR_ALLOCATE(stSizeInBytes, stAlignment, eEventType, \
	bProvideAccurateSizeOnDeallocate, pcSourceFile, iSourceLine, pcFunction) \
	mAllocator->Allocate(stSizeInBytes, stAlignment, eEventType \
	, bProvideAccurateSizeOnDeallocate, pcSourceFile, iSourceLine, pcFunction)

#define ALLOCTOR_REALLOCATE(pvMem, stSizeInBytes, stAlignment, eEventType, \
	bProvideAccurateSizeOnDeallocate, stSizeCurrent, pcSourceFile, iSourceLine, pcFunction) \
	mAllocator->Reallocate(pvMem, stSizeInBytes, stAlignment, eEventType, \
	bProvideAccurateSizeOnDeallocate, stSizeCurrent, pcSourceFile, iSourceLine, pcFunction)

#else // #ifdef GN_MEMORY_DEBUGGER

#define ALLOCTOR_ALLOCATE(stSizeInBytes, stAlignment, eEventType, \
	bProvideAccurateSizeOnDeallocate, pcSourceFile, iSourceLine, pcFunction) \
	mAllocator->Allocate(stSizeInBytes, stAlignment, eEventType \
	, bProvideAccurateSizeOnDeallocate) \

#define ALLOCTOR_REALLOCATE(pvMem, stSizeInBytes, stAlignment, eEventType, \
	bProvideAccurateSizeOnDeallocate, stSizeCurrent, pcSourceFile, iSourceLine, pcFunction) \
	mAllocator->Reallocate(pvMem, stSizeInBytes, stAlignment, eEventType, \
	bProvideAccurateSizeOnDeallocate, stSizeCurrent)

#endif // #ifdef GN_MEMORY_DEBUGGER

#endif // GNMEMORYMANAGER_H
