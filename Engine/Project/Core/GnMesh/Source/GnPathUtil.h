#ifndef __Core__GnPathUtil__
#define __Core__GnPathUtil__

#include "CCFileUtils.h"

inline static const gchar* GetFullPath(const gchar* pcFileName, const gchar* pcRelativeFile) {
	return cocos2d::CCFileUtils::fullPathFromRelativeFile( pcFileName, pcRelativeFile );
}

inline static const gchar* GetFullPath(const gchar* pcFileName) {
	return cocos2d::CCFileUtils::fullPathFromRelativePath( pcFileName );
}

#endif
