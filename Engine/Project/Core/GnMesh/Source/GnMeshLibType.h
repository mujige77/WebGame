#ifndef GNMESHLIBTYPE_H
#define GNMESHLIBTYPE_H

#ifdef GNMESH_EXPORT
// DLL library project uses this
#define GNMESH_ENTRY __declspec(dllexport)
#else
#ifdef GNMESH_IMPORT
// client of DLL uses this
#define GNMESH_ENTRY __declspec(dllimport)
#else
// static library project uses this
#define GNMESH_ENTRY
#endif
#endif	// GNMESH_EXPORT

#endif // GNMESHLIBTYPE_H
