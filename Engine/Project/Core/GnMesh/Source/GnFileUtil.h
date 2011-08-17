//
//  GnFileUtil.h
//  Core
//
//  Created by Max Yoon on 11. 8. 11..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GnFileUtil__
#define __Core__GnFileUtil__

class GnFileUtil
{
public:
	static bool FileCopy(const char* pcSrcPath, const char* pcDestPath);
	static bool ExitsFile(const char* pcFilePath);
};

#endif
