#include "GnToolLibPCH.h"
#include "GtToolSettings.h"

char GtToolSettings::mWorkPath[GN_MAX_PATH] = {"..\\Data\\"};

void GtToolSettings::EBMStartup()
{
	LoadFile();
	CreateWorkDirectory();
	GnTexture::SetTextureWorkPath( mWorkPath );
	GnSystem::SetWorkDirectory( mWorkPath );
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

	fprintf_s( fp,"%s\n", mWorkPath );

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
	scanf_s ( buffer, "%s", mWorkPath, 512 );

	GnPath::GetFullPathA( mWorkPath, buffer, MAX_LINE );
	GnStrcpy( mWorkPath, buffer, 260 );
	fclose( fp );
}

void GtToolSettings::SetWorkPath(char* path)
{
	GnStrcpy( mWorkPath, path, sizeof( mWorkPath ) );
}

char* GtToolSettings::GetWorkPath()
{
	return mWorkPath;
}

void GtToolSettings::MakeSaveFilePath(const gchar* pcFileName, const gchar* pcFolder, char* outPath, gsize outSize)
{
	GnStrcpy( outPath, mWorkPath, outSize );
	if( pcFolder )
	{
		GnStrcat( outPath, pcFolder, outSize );	
		GnStrcat( outPath, "\\", outSize );
	}
	GnStrcat( outPath, pcFileName, outSize );	
	gsize length = GnStrlen( outPath );
	outPath[length+1] = '\0';
}

void GtToolSettings::CreateWorkDirectory()
{
	::CreateDirectoryA( mWorkPath, NULL );
}

void GtToolSettings::CreateDirectoryInWorkDirectory(const gchar* pcFolderName)
{
	gchar folderPath[GN_MAX_PATH] = { 0, };
	GnStrcpy( folderPath, mWorkPath, sizeof(folderPath) );
	GnStrcat( folderPath, pcFolderName, sizeof(folderPath) );
	::CreateDirectoryA( folderPath, NULL );
}