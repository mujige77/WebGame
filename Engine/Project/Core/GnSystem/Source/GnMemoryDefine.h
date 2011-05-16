#ifndef GNMEMORYDEFINES_H
#define	GNMEMORYDEFINES_H

#include "GnSystemLibType.h"
#include "GnDebug.h"
#ifdef _PS3
#include <stddef.h>
#include <alloca.h>
#elif __APPLE__
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#if (GN_USE_MEMORY_MANAGEMENT >= 1) && !defined(GN_MEMORY_DEBUGGER)
#define  GN_MEMORY_DEBUGGER
#endif // (GN_USE_MEMORY_MANAGEMENT) && !defined(GN_MEMORY_DEBUGGER)

enum GnMemoryEventType
{
	GN_UNKNOWN = 0,                 // Unknown allocation/deallocation type.
	// This type will cause assertions in
	// the memory management interfaces.
	GN_OPER_NEW,                    // Allocated through GnNew. 
	// Should be deallocated with GnDelete
	GN_OPER_NEW_ARRAY,              // Allocated through GnNew[]. 
	// Should be deallocated with GnDelete[]
	GN_OPER_DELETE,                 // Deallocated with GnDelete.

	GN_OPER_DELETE_ARRAY,           // Deallocated with GnDelete[]

	GN_MALLOC,                      // Allocated through GnMalloc.
	// Should be deallocated with GnFree
	GN_REALLOC,                     // Allocated through GnRealloc.
	// Should be deallocated with GnFree.
	GN_ALIGNEDMALLOC,               // Allocated through GnAlignedAlloc.
	// Should be deallocated with 
	// GnAlignedFree
	GN_ALIGNEDREALLOC,              // Allocated through GnAlignedRealloc.
	// Should be deallocated with 
	// GnAlignedFree
	GN_FREE,                        // Deallocated with GnFree
	GN_ALIGNEDFREE,                 // Deallocated with GnAlignedFree
	GN_EXTERNALALLOC,               // Used to track external allocations
	GN_EXTERNALFREE                 // Used to track external frees
};

#define GN_MEM_FILE_DEFAULT 0
#define GN_MEM_LINE_DEFAULT -1
#define GN_MEM_FUNCTION_DEFAULT 0
#define GN_MEM_DEALLOC_SIZE_DEFAULT (gsize)-1

#ifdef _XENON
#define GN_MEM_ALIGNMENT  16
#elif defined(_PS3)
#define GN_MEM_ALIGNMENT  16
#else
#define GN_MEM_ALIGNMENT  4
#endif

#define GnExternalNew new
#define GnExternalDelete delete
#define GnExternalAlloc(T, count) ((T*)malloc(sizeof(T)*(count)))
#define GnExternalMalloc malloc
#define GnExternalRealloc realloc
#define GnExternalFree free
#define GnExternalCalloc calloc

#ifdef _PS3
	#define GnExternalAlignedMalloc(size, alignment) memalign(alignment, size)
	#define GnExternalAlignedRealloc reallocalign
	#define GnExternalAlignedFree free
	#define GnAlignOf(T) __alignof__(T)
	#define GnStackAlloc(T, count) (T*)alloca(sizeof(T)*(count))
	#define GnStackFree(x)
#else // #ifdef _PS3
    #ifdef WIN32
        #define GnExternalAlignedMalloc _aligned_malloc
        #define GnExternalAlignedRealloc _aligned_realloc
        #define GnExternalAlignedFree _aligned_free
    #else // #ifdef WIN32
        #define GnExternalAlignedMalloc(size, alignment) malloc(size)
        #define GnExternalAlignedRealloc(pvMemory, stSizeInBytes, stAlignment) realloc(pvMemory, stSizeInBytes)
        #define GnExternalAlignedFree free
    #endif // #ifdef WIN32
	#define GnAlignOf(T) __alignof(T)
	#define GnStackAlloc(T, count) (T*)_malloca(sizeof(T)*(count))
	#define GnStackFree _freea

#endif // #ifdef _PS3


GNSYSTEM_ENTRY void _GnFree(void* pvMemory);
GNSYSTEM_ENTRY void _GnAlignedFree(void* pvMemory);
#define GnFree(p) _GnFree(p)
#define GnAlignedFree(p) _GnAlignedFree(p)

#if defined(GN_MEMORY_DEBUGGER)

    GNSYSTEM_ENTRY void* _GnMalloc(gsize stSizeInBytes, 
        const char* pcSourceFile, int iSourceLine, const char* pcFunction);
    GNSYSTEM_ENTRY void* _GnAlignedMalloc(gsize stSizeInBytes, gsize stAlignment,
        const char* pcSourceFile, int iSourceLine, const char* pcFunction);
    GNSYSTEM_ENTRY void* _GnRealloc(void *memblock, gsize stSizeInBytes, 
        const char* pcSourceFile, int iSourceLine, const char* pcFunction); 
    GNSYSTEM_ENTRY void* _GnAlignedRealloc(void *memblock, gsize stSizeInBytes,
        gsize stAlignment, const char* pcSourceFile, int iSourceLine, const char* pcFunction); 
    GNSYSTEM_ENTRY int GnVerifyAddress(const void* pvMemory);

    #define GnAlloc(T, count) ((T*)_GnMalloc(sizeof(T)*(count), \
        __FILE__, __LINE__, __FUNCTION__)) 
    #define GnAlignedAlloc(T, count, alignment) ((T*)_GnAlignedMalloc( \
        sizeof(T)*(count), alignment, __FILE__, __LINE__, __FUNCTION__)) 
    #define GnAlignedMalloc(size, alignment) (_GnAlignedMalloc(size, \
        alignment, __FILE__, __LINE__, __FUNCTION__)) 
    #define GnMalloc(size) (_GnMalloc(size, \
        __FILE__, __LINE__, __FUNCTION__)) 
    #define GnRealloc(memblock, size) (_GnRealloc(memblock, size, \
        __FILE__, __LINE__, __FUNCTION__)) 
    #define GnAlignedRealloc(memblock, size, alignment) (_GnAlignedRealloc( \
        memblock, size, alignment, __FILE__, __LINE__, __FUNCTION__))


    #define GnNew new(__FILE__,__LINE__,__FUNCTION__)
    #define GnDelete delete

#else // #if defined(GN_MEMORY_DEBUGGER)

    GNSYSTEM_ENTRY void* _GnMalloc(gsize stSizeInBytes);
    GNSYSTEM_ENTRY void* _GnAlignedMalloc(gsize stSizeInBytes, gsize stAlignment);
    GNSYSTEM_ENTRY void* _GnRealloc(void *memblock, gsize stSizeInBytes); 
    GNSYSTEM_ENTRY void* _GnAlignedRealloc(void *memblock, gsize stSizeInBytes, gsize stAlignment);
    #define GnVerifyAddress(x) false

    #define GnAlloc(T, count) ((T*)_GnMalloc(sizeof(T)*(count)))
    #define GnAlignedAlloc(T, count, alignment) ((T*)_GnAlignedMalloc(sizeof(T)*(count), alignment))
    #define GnAlignedMalloc(size, alignment) (_GnAlignedMalloc(size, alignment)) 
    #define GnMalloc(size) (_GnMalloc(size)) 
    #define GnRealloc(memblock, size) (_GnRealloc(memblock, size))
    #define GnAlignedRealloc(memblock, size, alignment) (_GnAlignedRealloc(memblock, size, alignment))

    #define GnNew new
    #define GnDelete delete

#endif // #if defined(GN_MEMORY_DEBUGGER)

#if defined(GN_MEMORY_DEBUGGER) && defined(GNDEBUG)

	#define GnMemAssert(value) {GnAssert(value);}
	#define GnMemAssertUnit(value, unit) {GnAssert(value);}

#elif defined(GN_MEMORY_DEBUGGER) && !defined(GNDEBUG)

	#define GNMEMASSERT(value) {bool bValue = 0 != (value); \
		if (!bValue) {GnMeomeyAssert(#value, 0, __FILE__, __LINE__, \
		__FUNCTION__);}}
	#define GNMEMASSERTUNIT(value, unit) {bool bValue = (bool)(value); \
		if (!bValue) {GnMeomeyAssert(#value, pkUnit, __FILE__, __LINE__, \
		__FUNCTION__);}}

#else

	#define GNMEMASSERT(value) (void)0
	#define GNMEMASSERTUNIT(value, unit) (void)0

#endif // if defined(NI_MEMORY_DEBUGGER)

#define GnSafeDelete(object) if(object) GnDelete object; object = NULL


#endif // #ifndef GNMEMORYDEFINES_H