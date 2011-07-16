#ifndef __Core__GnPathUtil__
#define __Core__GnPathUtil__

#include "CCFileUtils.h"

inline static const gchar* GetFullPath(const gchar* pcFileName, const gchar* pcRelativeFile) {
	return cocos2d::CCFileUtils::fullPathFromRelativeFile( pcFileName, pcRelativeFile );
}

inline static const gchar* GetFullPath(const gchar* pcFileName) {
	return cocos2d::CCFileUtils::fullPathFromRelativePath( pcFileName );
}

inline static void GetFullPathFromWorkPath(const gchar* pcFileNamem, gstring& outString) {
	gchar fullPath[GN_MAX_PATH] = { 0, };
	const char* workDir = GnSystem::GetWorkDirectory();
	GnSprintf( fullPath, sizeof(fullPath), "%s%s", workDir, pcFileNamem );
	outString = fullPath;	
}

#endif
