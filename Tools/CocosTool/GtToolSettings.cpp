#include "StdAfx.h"
#include "GtToolSettings.h"

char GtToolSettings::mWorkPath[GN_MAX_PATH] = {"../Data/"};
gchar GtToolSettings::mBackgroundFile[GN_MAX_PATH]  = { 0, };
gint32 GtToolSettings::mScalePercent = 100;


void GtToolSettings::EBMStartup()
{
	LoadFile();
	CreateWorkDirectory();
	GnTexture::SetTextureWorkPath( mWorkPath );
	GnSystem::SetWorkDirectory( mWorkPath );
	GetGameState()->SetGameScale( GetScale() );
}

void GtToolSettings::EBMShutdown()
{
	SaveFile();
}

const int MAX_LINE = 1024;
void GtToolSettings::SaveFile()
{
	FILE *fp = NULL;
	errno_t err = fopen_s( &fp, "system.ini", "w" );

	if( err )
		return;

	fprintf( fp, "%s\n", mWorkPath );
	fprintf( fp, "%s\n", mBackgroundFile );
	fprintf( fp, "%d\n", mScalePercent );

	fclose(fp);
}

void GtToolSettings::LoadFile()
{
	FILE *fp = NULL;
	errno_t err = fopen_s( &fp, "system.ini", "r" );
	if( err )
		return;
	char buffer[MAX_LINE] = {0,};

	fgets( buffer, MAX_LINE, fp );
	if( size_t len = GnStrlen( buffer ) )
		strncpy_s( mWorkPath, GN_MAX_PATH, buffer, len - 1 );

	fgets( buffer, MAX_LINE, fp );
	if( size_t len = GnStrlen( buffer ) )
		strncpy_s( mBackgroundFile, GN_MAX_PATH, buffer, len - 1 );

	fgets( buffer, MAX_LINE, fp );
	if( size_t len = GnStrlen( buffer ) )
		sscanf_s(buffer, "%d", &mScalePercent );

	GnPath::GetFullPathA( mWorkPath, buffer, MAX_LINE );
	GnStrcpy( mWorkPath, buffer, 260 );
	fclose( fp );
}

void GtToolSettings::MakeSaveFilePath(const gchar* pcFileName, const gchar* pcFolder, char* outPath
	, gsize outSize)
{
	GnStrcpy( outPath, mWorkPath, outSize );
	if( pcFolder )
	{
		GnStrcat( outPath, pcFolder, outSize );	
		GnStrcat( outPath, "/", outSize );
	}
	GnStrcat( outPath, pcFileName, outSize );	
	gsize length = GnStrlen( outPath );
	outPath[length+1] = '\0';
}

void GtToolSettings::CreateWorkDirectory()
{
	::CreateDirectoryA( mWorkPath, NULL );
	
	std::string workDataPath = mWorkPath;
	workDataPath =+ gsActorPath;
	::CreateDirectoryA( mWorkPath, NULL );

	for( gtuint i = 0 ; i < TYPE_2DOBJECT_MAX; i++ )
	{
		workDataPath = mWorkPath;
		workDataPath += gs2DObjectPath[i];
		::CreateDirectoryA( workDataPath.c_str(), NULL );
	}
}

void GtToolSettings::CreateDirectoryInWorkDirectory(const gchar* objectType, const gchar* pcFolderName)
{
	gchar folderPath[GN_MAX_PATH] = { 0, };
	GnStrcpy( folderPath, mWorkPath, sizeof(folderPath) );
	GnStrcat( folderPath, objectType, sizeof(folderPath) );
	GnStrcat( folderPath, pcFolderName, sizeof(folderPath) );
	::CreateDirectoryA( folderPath, NULL );
}
void GtToolSettings::SetWorkPath(const char* path)
{
	GnStrcpy( mWorkPath, path, sizeof( mWorkPath ) );
}

char* GtToolSettings::GetWorkPath()
{
	return mWorkPath;
}

void GtToolSettings::SetBackgroundFilePath(const char* pcPath)
{
	GnStrcpy( mBackgroundFile, pcPath, sizeof( mBackgroundFile ) );
}

gchar* GtToolSettings::GetBackgroundFilePath()
{
	return mBackgroundFile;
}

gint32 GtToolSettings::GetScalePercent()
{
	return mScalePercent;
}

void GtToolSettings::SetScalsePercent(gint32 iScale)
{
	mScalePercent = iScale;
}

float GtToolSettings::GetScale()
{
	return (float)mScalePercent / 100.0f;
}