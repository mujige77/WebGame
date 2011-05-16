#ifndef GNDIRECTX9RENDERERTYPE_H
#define GNDIRECTX9RENDERERTYPE_H



#ifdef GNDIRECTX9RENDERER_EXPORT
// DLL library project uses this
#define GNDIRECTX9RENDERER_ENTRY __declspec(dllexport)
#else
#ifdef GNDIRECTX9RENDERER_IMPORT
// client of DLL uses this
#define GNDIRECTX9RENDERER_ENTRY __declspec(dllimport)
#else
// static library project uses this
#define GNDIRECTX9RENDERER_ENTRY
#endif
#endif	// GNSYSTEM_EXPORT

#endif // GNDIRECTX9RENDERERTYPE_H
