#ifndef GNMAINLIBTYPE_H
#define GNMAINLIBTYPE_H

#ifdef GNMAIN_EXPORT
// DLL library project uses this
#define GNMAIN_ENTRY __declspec(dllexport)
#else
#ifdef GNMAIN_IMPORT
// client of DLL uses this
#define GNMAIN_ENTRY __declspec(dllimport)
#else
// static library project uses this
#define GNMAIN_ENTRY
#endif
#endif	// GNMAIN_EXPORT

#endif // GNMAINLIBTYPE_H
