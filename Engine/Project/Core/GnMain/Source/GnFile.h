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
		READ_ACSII,
		WRITE_ACSII,
		APPEND_ACSII,
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
	static gchar* CopyAsciiFileString(const gchar* pcBuffer);
	
	void Destory();

	inline GnFile::eOpenMode GetMode() {
		return mMode;
	}
	inline char* ReadLine() {
		GnAssert( mMode <= NUM_OPENMODE && mMode > APPEND_BIANRY );
		fgets( mpBuffer, mBufferAllocSize, mpFile );
		return mpBuffer;
	}
	inline void WriteLine(const gchar* pcBuffer) {
		GnAssert( mMode <= NUM_OPENMODE && mMode > APPEND_BIANRY );
		fprintf( mpFile, "%s", pcBuffer );
	}
	GNFORCEINLINE gsize LoadBinary( void* pBuffer, gsize size ) {
		return fread( pBuffer, size, 1, mpFile );
	}
	
	GNFORCEINLINE gsize SaveBinary( const void * pBuffer, gsize size ) {
		return fwrite( pBuffer, size, 1, mpFile );
	}
	
	inline bool IsExist() {
		return feof( mpFile ) == 0;
	}

protected:
	GnFile(FILE* pOpenedFile, eOpenMode eMode, gtuint uiBufferSize = 2048);	
	
};

#endif // GNFILE_H