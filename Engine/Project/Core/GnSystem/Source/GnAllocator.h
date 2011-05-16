#pragma once
#ifndef GNALLOCATOR_H
#define GNALLOCATOR_H


class GNSYSTEM_ENTRY GnAllocator
{
public:	
	virtual ~GnAllocator(){};
#ifdef GN_MEMORY_DEBUGGER
	virtual void* Allocate(
		gsize& stSizeInBytes, 
		gsize& stAlignment,
		GnMemoryEventType eEventType, 
		bool bProvideAccurateSizeOnDeallocate,
		const char* pcFile, 
		int iLine,
		const char* pcFunction) = 0;

	virtual void* Reallocate(
		void* pvMemory, 
		gsize& stSizeInBytes,
		gsize& stAlignment, 
		GnMemoryEventType eEventType, 
		bool bProvideAccurateSizeOnDeallocate,
		gsize stSizeCurrent,
		const char* pcFile, int iLine,
		const char* pcFunction) = 0;

	// Functions to allow tracking of memory. These functions should NOT
	// touch the input addresses in any way.
	virtual bool TrackAllocate(
		const void* const pvMemory, 
		gsize stSizeInBytes, 
		GnMemoryEventType eEventType, 
		const char* pcFile, 
		int iLine,
		const char* pcFunction) = 0;

	virtual bool TrackDeallocate(
		const void* const pvMemory, 
		GnMemoryEventType eEventType) = 0;

	virtual bool SetMarker(const char* pcMarkerType, const char* pcClassifier,
		const char* pcString) =0;

	virtual bool VerifyAddress(const void* pvMemory) = 0;

#else // GN_MEMORY_DEBUGGER

	virtual void* Allocate(
		gsize& stSizeInBytes, 
		gsize& stAlignment,
		GnMemoryEventType eEventType, 
		bool bProvideAccurateSizeOnDeallocate) = 0;

	virtual void* Reallocate(
		void* pvMemory, 
		gsize& stSizeInBytes,
		gsize& stAlignment, 
		GnMemoryEventType eEventType, 
		bool bProvideAccurateSizeOnDeallocate,
		gsize stSizeCurrent) =0;

#endif // GN_MEMORY_DEBUGGER

	virtual void Deallocate(void* pvMemory, GnMemoryEventType eEventType, 
		gsize stSizeInBytes) = 0;

	// Called by the memory manager during GnInit()
	virtual void Initialize() = 0;
	// Called by the memory manager during GnShutdown()
	virtual void Shutdown() = 0;
};

#endif // GNALLOCATOR_H