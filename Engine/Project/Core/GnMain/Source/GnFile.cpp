#include "GnMainPCH.h"
#include "GnFile.h"

GnFile::GnFile(FILE* pOpenedFile, eOpenMode eMode, gtuint uiBufferSize) : mpFile(pOpenedFile),
	mBufferAllocSize(uiBufferSize)
{
	mpBuffer = GnAlloc(gchar, uiBufferSize);
}

GnFile::~GnFile()
{
	if( mpBuffer )
		GnFree(mpBuffer);
	if( mpFile )
		fclose(mpFile);
}

GnFile* GnFile::GetFile(const gchar* strFileName, eOpenMode eMode, gtuint uiBufferSize)
{
	gchar stringOpenMode[NUM_OPENMODE][3] =
	{
		"rb",
		"wb",
		"ab"/*,
		"r",
		"w",
		"a"*/
	};
	FILE* file = NULL;
#ifdef WIN32
	errno_t err = GnFopen( &file, strFileName, stringOpenMode[eMode] );
#else
	file = GnFopen( strFileName, stringOpenMode[eMode] );
#endif
	if( file == NULL )
		return NULL;

	GnFile* gnfile = GnNew GnFile( file, eMode, uiBufferSize );
	return gnfile;
}