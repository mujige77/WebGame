#ifndef GNLOG_H
#define GNLOG_H
#include "GnTCharFunctions.h"

GNSYSTEM_ENTRY void WriteOutputDebug(gtchar* format, ...);
GNSYSTEM_ENTRY void WriteOutputDebugA(char* format, ...);
GNSYSTEM_ENTRY void WriteOutputFileA(char* format, ...);


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

