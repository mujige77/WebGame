#pragma once
#include "GnAllocator.h"

#ifdef GN_MEMORY_DEBUGGER

//#ifdef WIN32
#include <map>
//#endif // WIN32

class GnAllocUnit 
{
public:
	void* mpMeomry;
	size_t mAllocSize;	
	char maFileName[256];
	char maFunctionName[256];
	int mFileLine;
};
class GNSYSTEM_ENTRY GnDebugAllocator : public GnAllocator
{
public:
	GnDebugAllocator(GnAllocator* actualAllocator, bool writeToLog = true,
		gtuint initialSize = 65536, gtuint growBy = 4096,
		bool alwaysValidateAll = false, bool checkArrayOverruns = true);
	virtual ~GnDebugAllocator(void);

	// Encapsulate all memory management through a 
	// single set of API calls.

	// Note that the size and alignment are passed-by-reference. 
	// This allows the allocator to adjust the values
	// internally and pass the results back to the caller.
	virtual void* Allocate(gsize& stSizeInBytes, gsize& stAlignment,
		GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate,
		const gchar* pcFile, int iLine, const gchar* pcFunction);

	virtual void Deallocate(void* pvMemory, GnMemoryEventType eEventType, 
		gsize stSizeInBytes);

	virtual void* Reallocate(void* pvMemory, gsize& stSizeInBytes,
		gsize& stAlignment, GnMemoryEventType eEventType, 
		bool bProvideAccurateSizeOnDeallocate, gsize stSizeCurrent,
		const gchar* pcFile, int iLine, const gchar* pcFunction);

	virtual bool TrackAllocate(const void* const pvMemory, gsize stSizeInBytes, 
		GnMemoryEventType eEventType, const gchar* pcFile, 
		int iLine, const gchar* pcFunction);

	virtual bool TrackDeallocate(const void* const pvMemory, GnMemoryEventType eEventType);

	virtual bool SetMarker(const char* pcMarkerType, const char* pcClassifier,
		const char* pcString);

	virtual void Initialize();

	virtual void Shutdown();

	virtual bool VerifyAddress(const void* pvMemory);

	gsize PadForArrayOverrun(gsize stAlignment, gsize stSizeOriginal);
	void AllocateAssert(const gchar* allocateFunction, gsize ID, gsize size);

protected:
	bool mCheckArrayOverruns;
	GnAllocator* mActualAlloctor;
//#ifdef WIN32
	std::map<void*, GnAllocUnit> mpAllocList;
//#endif // WIN32	
};

#endif // GN_MEMORY_DEBUGGER
