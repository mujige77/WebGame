#ifndef GNPATH_H
#define GNPATH_H

#include "GnSystemDefine.h"

#if defined(_MAX_PATH)
#define GN_MAX_PATH _MAX_PATH
#else //#if defined(_MAX_PATH)
#define GN_MAX_PATH 260
#endif //#if defined(_MAX_PATH)

class GNSYSTEM_ENTRY GnPath
{
protected:
	gtchar* mFullFilePath;
	gtchar* mFileName;
	gtchar* mFileExtension;
public:
	static size_t ConvertToAbsolute(
		gchar* pcAbsolutePath,
		size_t stBytes, 
		const gchar* pcRelativePath, 
		const gchar* pcRelativeToHere);

	static bool GetFileName(const gwchar* pcFilePath,  gwchar* pcOutName, gsize maxPathLength, bool hasExtension = false);
	static bool GetFullPath(const gwchar* pcFilePath,  gwchar* pcOutPath, gsize maxPathLength);
	static bool GetFileNameA(const gchar* pcFilePath,  gchar* pcOutName, gsize maxPathLength, bool hasExtension = false);
	static bool GetFullPathA(const gchar* pcFilePath,  gchar* pcOutPath, gsize maxPathLength);
	static bool CheckSamePathA(const gchar* pcPath1,  const gchar* pcPath2);
};

#endif // GNPATH_H