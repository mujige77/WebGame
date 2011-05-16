#ifndef GTTOOLLIBTYPE_H
#define GTTOOLLIBTYPE_H

#ifdef GNTOOLLIB_EXPORT
// DLL library project uses this
#define GTTOOLLIB_ENTRY __declspec(dllexport)
#else
// client of DLL uses this
#define GTTOOLLIB_ENTRY __declspec(dllimport)

#endif	// GNMAIN_EXPORT

#endif // GTTOOLLIBTYPE_H