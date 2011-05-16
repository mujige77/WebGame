#include "GnSystemPCH.h"
#include "GnDebugAllocator.h"

#ifdef GN_MEMORY_DEBUGGER
GnDebugAllocator::GnDebugAllocator(GnAllocator* actualAllocator, bool writeToLog,
	gtuint initialSize, gtuint growBy, bool alwaysValidateAll,bool checkArrayOverruns)
	: mActualAlloctor(actualAllocator)
{
}

GnDebugAllocator::~GnDebugAllocator(void)
{
	GnExternalDelete mActualAlloctor;
}

void* GnDebugAllocator::Allocate(gsize& sizeInBytes, gsize& alignment,
	GnMemoryEventType eventType, bool provideAccurateSizeOnDeallocate, const gchar* pcFile,
	int iLine, const gchar* allocateFunction)
{
	//gsize stSizeOriginal = sizeInBytes;
	//float fTime = GnGetCurrentTimeInSec();

	//if( mCheckArrayOverruns )
	//{
	//	sizeInBytes = PadForArrayOverrun(alignment, sizeInBytes);
	//}
	//fTime = GnGetCurrentTimeInSec() - fTime;
	void* memory =  mActualAlloctor->Allocate(sizeInBytes, alignment, eventType, provideAccurateSizeOnDeallocate,
		pcFile, iLine, allocateFunction);

#if WIN32	
	GnAllocUnit unit;
	unit.mpMeomry = memory;
	unit.mAllocSize = sizeInBytes;
	GnStrcpy( unit.maFileName, pcFile, sizeof( unit.maFileName ) );
	unit.mFileLine = iLine;	
	GnStrcpy( unit.maFunctionName, allocateFunction, sizeof( unit.maFunctionName ) );	
	mpAllocList.insert(std::make_pair(memory, unit));	
#endif //
		
	return memory;
}

void GnDebugAllocator::Deallocate(void* pvMemory, GnMemoryEventType eEventType, 
	gsize stSizeInBytes)
{
#if WIN32	
	mpAllocList.erase(pvMemory);
#endif //
	mActualAlloctor->Deallocate(pvMemory, eEventType, stSizeInBytes);
}

void* GnDebugAllocator::Reallocate(void* pvMemory, gsize& stSizeInBytes,
	gsize& stAlignment, GnMemoryEventType eEventType, 
	bool bProvideAccurateSizeOnDeallocate, gsize stSizeCurrent,
	const gchar* pcFile, int iLine, const gchar* pcFunction)
{
	return mActualAlloctor->Reallocate(pvMemory, stSizeInBytes, stAlignment, eEventType,
		bProvideAccurateSizeOnDeallocate, stSizeCurrent, pcFile, iLine, pcFunction);
}

bool GnDebugAllocator::TrackAllocate(const void* const pvMemory, gsize stSizeInBytes,
   GnMemoryEventType eEventType, const gchar* pcFile,
   int iLine, const gchar* pcFunction)
{
	return true;
}

bool GnDebugAllocator::TrackDeallocate(const void* const pvMemory, GnMemoryEventType eEventType)
{
	return true;
}

bool GnDebugAllocator::SetMarker(const char* pcMarkerType, const char* pcClassifier,
	const char* pcString)
{
	return true;
}

void GnDebugAllocator::Initialize()
{
}

void GnDebugAllocator::Shutdown()
{
#ifdef WIN32
	std::map<void*, GnAllocUnit>::iterator iter = mpAllocList.begin();
	while(iter != mpAllocList.end())
	{
		GnAllocUnit item = iter->second;
		GnLogA( "Memory Leak %d : Size =  %d, %s %s %d\n" ,
			item.mpMeomry,
			item.mAllocSize,
			item.maFileName,
			item.maFunctionName,
			item.mFileLine );
		++iter;
	}
#endif // WIN32
}

bool GnDebugAllocator::VerifyAddress(const void* pvMemory)
{
	return false;
}
//---------------------------------------------------------------------------
gsize GnDebugAllocator::PadForArrayOverrun(gsize stAlignment, gsize stSizeOriginal)
{
	return stSizeOriginal + 2 * stAlignment;
}

void GnDebugAllocator::AllocateAssert(const gchar* allocateFunction, gsize ID, gsize size)
{
	//// If you hit this NIMEMASSERT, you requested a breakpoint on a specific 
	//// function name.
	//GnAssert(strcmp(ms_pcBreakOnFunctionName, pcFunction) != 0);

	//// If you hit this NIMEMASSERT, you requested a breakpoint on a specific 
	//// allocation ID.
	//GnAssert(ms_stBreakOnAllocID != m_stCurrentAllocID);

	//// If you hit this NIMEMASSERT, you requested a breakpoint on a specific 
	//// allocation request size.
	//GnAssert(ms_stBreakOnSizeRequested != stSizeOriginal);
}
#endif // #ifdef GN_MEMORY_DEBUGGER