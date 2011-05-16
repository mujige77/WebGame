#ifndef GNFILE_H
#define GNFILE_H

#ifdef WIN32
#define GnFopen fopen_s
#else // WIN32
#define GnFopen fopen
#endif // WIN32

class GnFile : public GnMemoryObject
{
public:
	enum eOpenMode
	{
		READ_BIANRY,
		WRITE_BIANRY,
		APPEND_BIANRY,
		//READ_ACSII,
		//WRITE_ACSII,
		//APPEND_ACSII,
		NUM_OPENMODE,
	};

protected:
	gtuint mBufferAllocSize;
	FILE* mpFile;
	char* mpBuffer;
	eOpenMode mMode;	

public:
	virtual ~GnFile();
	static GnFile* GetFile(const gchar* strFileName, eOpenMode eMode, gtuint uiBufferSize = 2048);

	inline GnFile::eOpenMode GetMode() {
		return mMode;
	}
	GNFORCEINLINE gsize LoadBinary( void* pBuffer, gsize size );
	GNFORCEINLINE gsize SaveBinary( const void * pBuffer, gsize size );

protected:
	GnFile(FILE* pOpenedFile, eOpenMode eMode, gtuint uiBufferSize = 2048);	
	
};

GNFORCEINLINE gsize GnFile::LoadBinary( void* pBuffer, gsize size )
{
	return fread( pBuffer, size, 1, mpFile );
}

GNFORCEINLINE gsize GnFile::SaveBinary( const void * pBuffer, gsize size )
{
	return fwrite( pBuffer, size, 1, mpFile );
}


#endif // GNFILE_H