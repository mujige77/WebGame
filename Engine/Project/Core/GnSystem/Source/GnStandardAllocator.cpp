#include "GnSystemPCH.h"
#include "GnStandardAllocator.h"

#define IS_POWER_OF_TWO(x)   (((x)&(x-1)) == 0)

void* GnStandardAllocator::Allocate(gsize& stSizeInBytes, gsize& stAlignment,
	GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate)
{
	GnAssert(IS_POWER_OF_TWO(stAlignment));
	return GnExternalAlignedMalloc(stSizeInBytes, stAlignment);
}

void* GnStandardAllocator::Reallocate(void* pvMemory, gsize& stSizeInBytes,
	gsize& stAlignment, GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate,
	gsize stSizeCurrent)
{
	GnAssert(IS_POWER_OF_TWO(stAlignment));

	// The deallocation case should have been caught by us before in
	// the allocation functions.
	GnAssert(stSizeInBytes != 0);

	return GnExternalAlignedRealloc(pvMemory, stSizeInBytes, stAlignment);
}

void GnStandardAllocator::Deallocate(void* pvMemory, GnMemoryEventType eEventType, 
	gsize stSizeInBytes)
{
	if (pvMemory == NULL)
		return;

	GnExternalAlignedFree(pvMemory);
}

void GnStandardAllocator::Initialize()
{

}

void GnStandardAllocator::Shutdown()
{

}