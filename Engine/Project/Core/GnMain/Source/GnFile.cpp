#include "GnMainPCH.h"
#include "GnFile.h"

GnFile::GnFile(FILE* pOpenedFile, eOpenMode eMode, gtuint uiBufferSize) : mpFile(pOpenedFile),
	mMode(eMode), mBufferAllocSize(uiBufferSize)
{
	static guint i = 0;
	mNumber = i++;
	mpBuffer = GnAlloc(gchar, uiBufferSize);
}

GnFile::~GnFile()
{
	if( mpFile )
	{
		fclose(mpFile);	
	}
	if( mpBuffer )
		GnFree(mpBuffer);
}

GnFile* GnFile::GetFile(const gchar* strFileName, eOpenMode eMode, gtuint uiBufferSize)
{
	gchar stringOpenMode[NUM_OPENMODE][3] =
	{
		"rb",
		"wb",
		"ab",
		"r",
		"w",
		"a"
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

void GnFile::Destory()
{
	GnDelete this;
}

gchar* GnFile::CopyAsciiFileString(const gchar* pcBuffer)
{
	size_t len = GnStrlen( pcBuffer )-1;
	gchar* copyString = GnAlloc(gchar, len);
#if ( GNUSE_OS == PLATFORM_WIN32 )
	strcpy_s( copyString, sizeof( copyString ) * len , pcBuffer );
#else
	strcpy( copyString, pcBuffer );
#endif
	copyString[len-1] = '\0';
	return copyString;
}