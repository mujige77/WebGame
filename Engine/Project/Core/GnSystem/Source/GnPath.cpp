#include "GnSystemPCH.h"
#include "GnPath.h"

#ifdef WIN32
bool GnGetCurrentDirectory(gchar* pcStr, gtuint uiMaxSize)
{
	if( GetCurrentDirectoryA( uiMaxSize, pcStr ) == 0 )
		return false;
	return true;
}

#else
#endif

//---------------------------------------------------------------------------
gsize GnPath::ConvertToAbsolute(char* pcAbsolutePath, size_t stAbsBytes,	const char* pcRelativePath, const char* pcRelativeToHere)
{
	//// This function takes pcRelativePath and converts it to an absolute path 
	//// by concatenating it with pcRelativeToHere and removing dotdots.

	//// The resulting absolute path is stored in pcAbsolutePath, which is 
	//// assumed to have been allocated with size stAbsBytes. 
	//// The function returns the number of bytes written.

	//GnAssert(pcAbsolutePath && pcRelativePath);
	//GnAssert(IsRelative(pcRelativePath));
	//GnAssert(pcAbsolutePath != pcRelativePath); // destination cannot be source
	//
	//// If pcRelativeToHere is null or an empty string, use the current working
	//// directory.
	//if (!pcRelativeToHere)
	//{
	//	pcRelativeToHere = "";
	//}
	//size_t stLenRelativeToHere = strlen(pcRelativeToHere);
	//if (stLenRelativeToHere == 0)
	//{
	//	char acCWD[NI_MAX_PATH];
	//	if (!GnGetCurrentDirectory(acCWD, NI_MAX_PATH))
	//	{
	//		if (stAbsBytes > 0)
	//			pcAbsolutePath[0] = NULL;
	//		return 0;
	//	}
	//	GnAssert(strlen(acCWD) != 0);
	//	return ConvertToAbsolute(pcAbsolutePath, stAbsBytes, pcRelativePath, acCWD);
	//}

	//size_t stLenRelativePath = strlen(pcRelativePath);

	//// Concatenate a delimiter if necessary
	//bool bInsertDelimiter = 
	//	(pcRelativeToHere[stLenRelativeToHere-1] != NI_PATH_DELIMITER_CHAR);

	//size_t stRequiredSize = 1 // null termination
	//	+ stLenRelativeToHere 
	//	+ stLenRelativePath
	//	+ ((bInsertDelimiter) ? 1 : 0);

	//// Fail if not enough storage
	//if (stAbsBytes < stRequiredSize)
	//{
	//	if (stAbsBytes > 0)
	//		pcAbsolutePath[0] = NULL;
	//	return 0;
	//}

	//// Store pcRelativeToHere into pcAbsolutePath
	//GnStrcpy(pcAbsolutePath, pcRelativeToHere, stAbsBytes);

	//// Concatenate a delimiter if necessary
	//if (bInsertDelimiter)
	//	GnStrcat(pcAbsolutePath, NI_PATH_DELIMITER_STR, stAbsBytes);

	//// Concatenate pcRelativePath
	//GnStrcat(pcAbsolutePath, pcRelativePath);

	//RemoveDotDots(pcAbsolutePath);
	return strlen(pcAbsolutePath);
}

bool GnPath::GetFileName(const gwchar* pcFilePath, gwchar* pcOutName, gsize maxPathLength, bool hasExtension)
{
#ifdef WIN32
	gwchar strFullPath[GN_MAX_PATH];
	if( GetFullPath( pcFilePath, strFullPath, GN_MAX_PATH ) == false )
		return false; 

	gwchar strExtension[16];
	errno_t err = _wsplitpath_s( strFullPath, NULL, 0,  NULL, 0, pcOutName,  maxPathLength, strExtension, 16 );
	//_splitpath_s(strFullPath, drive, dir, NULL, NULL);
	if( err != 0 )
		return false;

	if( hasExtension )
		GnWStrcat( pcOutName, strExtension, maxPathLength );
	
#endif // WIN32
	return true;
}

bool GnPath::GetFullPath(const gwchar* pcFilePath,  gwchar* pcOutPath, gsize maxPathLength)
{
#ifdef WIN32
	if( _wfullpath( pcOutPath, pcFilePath, maxPathLength ) == NULL )
		return false;
#endif // WIN32
	return true;
}

bool GnPath::GetFileNameA(const gchar* pcFilePath,  gchar* pcOutName, gsize maxPathLength, bool hasExtension)
{
#ifdef WIN32
	gchar strFullPath[GN_MAX_PATH];
	if( GetFullPathA( pcFilePath, strFullPath, GN_MAX_PATH ) == false )
		return false; 

	gchar strExtension[16];
	errno_t err = _splitpath_s( strFullPath, NULL, 0,  NULL, 0, pcOutName,  maxPathLength, strExtension, 16 );
	if( err != 0 )
		return false;

	if( hasExtension )
		GnStrcat( pcOutName, strExtension, maxPathLength );

#endif // WIN32
	return true;
}

bool GnPath::GetFullPathA(const gchar* pcFilePath,  gchar* pcOutPath, gsize maxPathLength)
{
#ifdef WIN32
	if( _fullpath( pcOutPath, pcFilePath, maxPathLength ) == NULL )
		return false;
#endif // WIN32
	return true;
}

bool GnPath::CheckSamePathA(const gchar* pcPath1, const gchar* pcPath2)
{
	gchar strFullPath1[GN_MAX_PATH] = {0,};
	gchar strFullPath2[GN_MAX_PATH] = {0,};
	GetFullPathA( pcPath1, strFullPath1, GN_MAX_PATH );
	GetFullPathA( pcPath2, strFullPath2, GN_MAX_PATH );
	
	if( GnStricmp( strFullPath1, strFullPath2 ) != 0 )
		return false;

	return true;
}