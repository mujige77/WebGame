#ifndef GNSCREENMESHLIBTYPE_H
#define GNSCREENMESHLIBTYPE_H

#ifdef GNSCREENMESH_EXPORT
// DLL library project uses this
#define GNSCREENMESH_ENTRY __declspec(dllexport)
#else
#ifdef GNSCREENMESH_IMPORT
// client of DLL uses this
#define GNSCREENMESH_ENTRY __declspec(dllimport)
#else
// static library project uses this
#define GNSCREENMESH_ENTRY
#endif
#endif	// GNSCREENMESH_EXPORT

#endif // GNSCREENMESHLIBTYPE_H
