#ifndef GNSYSTEMLIBTYPE_H
#define GNSYSTEMLIBTYPE_H

#ifdef GNSYSTEM_EXPORT
    // DLL library project uses this
    #define GNSYSTEM_ENTRY __declspec(dllexport)
#else
    #ifdef GNSYSTEM_IMPORT
    // client of DLL uses this
        #define GNSYSTEM_ENTRY __declspec(dllimport)
    #else
    // static library project uses this
        #define GNSYSTEM_ENTRY
    #endif
#endif	// GNSYSTEM_EXPORT

#endif // GNSYSTEMLIBTYPE_H
