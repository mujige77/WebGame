#include "GnSystemPCH.h"
#include "GnMemoryObject.h"

#if !defined(NI_DISABLE_EXCEPTIONS)
#include <exception> // for std::bad_alloc
#include <new>
#endif

#ifdef GN_MEMORY_DEBUGGER
void* GnMemoryObject::operator new(gsize stSize)
#if defined(NI_DISABLE_EXCEPTIONS)
throw()
#endif
{
#if defined(NI_DISABLE_EXCEPTIONS)
	return NULL;
#else
	throw std::bad_alloc();
#endif
}

void* GnMemoryObject::operator new[](gsize stSize)
#if defined(NI_DISABLE_EXCEPTIONS)
throw()
#endif
{
#if defined(NI_DISABLE_EXCEPTIONS)
	return NULL;
#else
	throw std::bad_alloc();
#endif
}

void* GnMemoryObject::operator new(gsize stSizeInBytes, const char* pcSourceFile, 
	int iSourceLine, const char* pcFunction)
{
	if (stSizeInBytes == 0)
		stSizeInBytes = 1;

	void* p =  GnMemoryManager::Instance()->Allocate(stSizeInBytes, GN_MEM_ALIGNMENT, GN_OPER_NEW, true,
		pcSourceFile, iSourceLine, pcFunction);

#if !defined(NI_DISABLE_EXCEPTIONS)
	if (p == 0)
		throw std::bad_alloc();
#endif

	return p;
}

void* GnMemoryObject::operator new[](gsize stSizeInBytes, const char* pcSourceFile, 
	int iSourceLine, const char* pcFunction)
{
	if (stSizeInBytes == 0)
		stSizeInBytes = 1;

	void* p =  GnMemoryManager::Instance()->Allocate(stSizeInBytes, GN_MEM_ALIGNMENT, GN_OPER_NEW_ARRAY, false,
		pcSourceFile, iSourceLine, pcFunction);

#if !defined(NI_DISABLE_EXCEPTIONS)
	if (p == 0)
		throw std::bad_alloc();
#endif

	return p;
}
#else // #ifdef GN_MEMORY_DEBUGGER
void* GnMemoryObject::operator new(gsize stSizeInBytes)
{
	if (stSizeInBytes == 0)
		stSizeInBytes = 1;

	void* p =  GnMemoryManager::Instance()->Allocate(stSizeInBytes, GN_MEM_ALIGNMENT, GN_OPER_NEW, true);

#if !defined(NI_DISABLE_EXCEPTIONS)
	if (p == 0)
		throw std::bad_alloc();
#endif

	return p;
}
void* GnMemoryObject::operator new[](gsize stSizeInBytes)
{
	if (stSizeInBytes == 0)
		stSizeInBytes = 1;

	void* p =  GnMemoryManager::Instance()->Allocate(stSizeInBytes, GN_MEM_ALIGNMENT, GN_OPER_NEW_ARRAY, false);
	
#if !defined(NI_DISABLE_EXCEPTIONS)
	if (p == 0)
		throw std::bad_alloc();
#endif

	return p;
}
#endif // #ifdef GN_MEMORY_DEBUGGER

void GnMemoryObject::operator delete(void* pvMem, gsize stElementSize)
{
	if (pvMem)
	{
		GnMemoryManager::Instance()->Deallocate(pvMem, GN_OPER_DELETE, stElementSize);
	}
}

void GnMemoryObject::operator delete[](void* pvMem, gsize stElementSize)
{
	if (pvMem)
	{
		GnMemoryManager::Instance()->Deallocate(pvMem, GN_OPER_DELETE_ARRAY);
	} 
}

