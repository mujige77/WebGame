#ifndef GNMEMORY_H
#define GNMEMORY_H


class GNSYSTEM_ENTRY GnMemoryObject
{
#ifdef GN_MEMORY_DEBUGGER
private:
	static void* operator new(gsize stSize);
	static void* operator new[](gsize stSize);
public:
	static void *operator new(gsize stSize, const char *pcSourceFile, 
		int iSourceLine, const char* pcFunction);

	static void *operator new[](gsize stSize, const char *pcSourceFile, 
		int iSourceLine, const char* pcFunction);

	static void operator delete(void *pvMem, const char *pcSourceFile, 
		int iSourceLine, const char* pcFunction){}

	static void operator delete[](void *pvMem, const char *pcSourceFile, 
		int iSourceLine, const char* pcFunction){}
#else // #ifdef GN_MEMORY_DEBUGGER
public:
	static void* operator new(gsize stSize);
	static void* operator new[](gsize stSize);
#endif // #ifdef GN_MEMORY_DEBUGGER
public:

	static void operator delete(void *pvMem, gsize stElementSize);
	static void operator delete[](void *pvMem, gsize stElementSize);

	static void* operator new( gsize stSize, void* p ) { return p; }
	static void* operator new[]( gsize stSize, void* p ) { return p; }

	static void operator delete( void *, void* ) {}
	static void operator delete[]( void *, void* ) {}
};

#endif // GNMEMORY_H
