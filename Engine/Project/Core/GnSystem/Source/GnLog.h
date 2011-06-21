#ifndef GNLOG_H
#define GNLOG_H
#include "GnTCharFunctions.h"

GNSYSTEM_ENTRY void WriteOutputDebug(const gtchar* format, ...);
GNSYSTEM_ENTRY void WriteOutputDebugA(const gchar* format, ...);
GNSYSTEM_ENTRY void WriteOutputFileA(const gchar* format, ...);

#ifdef GNDEBUG
#define GnLog WriteOutputDebug
#define GnLogA WriteOutputDebugA
#elif GNLOG
#define GnLog WriteOutputDebug
#define GnLogA WriteOutputFileA
#else 
#define GnLog GNNOOP
#define GnLogA  GNNOOP
#endif // _DEBUG





#endif // GNLOG_H

