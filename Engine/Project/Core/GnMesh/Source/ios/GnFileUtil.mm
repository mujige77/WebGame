#import <Foundation/Foundation.h>
#include "GnFileUtil.h"


bool GnFileUtil::FileCopy(const char* pcSrcPath, const char* pcDestPath)
{
	NSFileManager *fileManager = [NSFileManager defaultManager];
	
	NSString* nsSrcPath = [NSString stringWithUTF8String: pcSrcPath];
	NSString* nsDestPath = [NSString stringWithUTF8String: pcDestPath];	
	
	NSError* error;
	BOOL success = [fileManager copyItemAtPath:nsSrcPath toPath:nsDestPath error:&error];	
	return success;
}

bool GnFileUtil::ExitsFile(const char* pcFilePath)
{
	NSFileManager *fileManager = [NSFileManager defaultManager];
	
	NSString* nsFilePath = [NSString stringWithUTF8String: pcFilePath];
	
	BOOL exits = [fileManager fileExistsAtPath:nsFilePath];	
	return exits;
}
