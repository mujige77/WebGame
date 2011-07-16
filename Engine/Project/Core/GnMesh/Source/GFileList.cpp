#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GFileList.h"


GFileList* GFileList::mpSingleton = CreateSingletonObjects(GFileList);

GFileList* GFileList::GetSingleton()
{
	return mpSingleton;
}

GnMemoryObject* GFileList::Create()
{
	mpSingleton = GnNew GFileList();
	return mpSingleton;
}

GFileList::GFileList()
{
	char name[512] = {0,};
	GnStrcpy( name, GetFullPath( "template.lst" ), 512);
	GnVerify( LoadFile( name ) );

}

bool GFileList::LoadFile(const gchar *pcFilePath)
{
	GnFile* file = GnFile::GetFile( pcFilePath, GnFile::READ_ACSII, 256 );
	if( file == NULL )
		return false;	
		
	ReadList( file, "ForcesList", mForcesNames );
	ReadList( file, "EnemyList", mEnemyNames );
	ReadList( file, "EffectList", mEffectNames );
	file->Destory();
	return true; 
}

bool GFileList::GetFullEffectName(gtuint uiIndex, gstring& outString)
{
	const gchar* name = GetEffectName( uiIndex );
	if( name == NULL )
		return false;
	
	gchar fullPath[GN_MAX_PATH] = { 0, };
	const char* workDir = GnSystem::GetWorkDirectory();
	GnSprintf( fullPath, sizeof(fullPath), "%sEffect/%s/%s.gm", workDir, name, name );
	outString = fullPath;
	return true;
}

void GFileList::ReadList(GnFile* pFile, const gchar* firstName, GnTPrimitiveDeleteMap<gtuint, gchar*>& names)
{
	
	char* buffer = pFile->ReadLine();
	const char* temp = NULL;
//	while (true)
//	{
//		if( pFile->IsExist() == false )
//		{
//			return;
//	 	}
//		buffer = pFile->ReadLine();
//		temp = GnStrstr( buffer, firstName );
//		if( temp != NULL )
//			break;		
//	}
	
	while (true)
	{
		buffer = pFile->ReadLine();	
		temp = GnStrstr( buffer, "EndList" );
		if( temp != NULL )
			break;
		AddListFromFile( buffer, names );
	}
}

void GFileList::AddListFromFile(gchar* buffer, GnTPrimitiveDeleteMap<gtuint, gchar*>& names)
{
	gchar tempString[16] = {0,};
	guint32 numID = 0;
#if ( GNUSE_OS != PLATFORM_WIN32 )
	sscanf( buffer, "%c%d", tempString, &numID );
#else
	sscanf_s( buffer, "%c%d", tempString, &numID );
#endif
	gchar* fileName = GnFile::CopyAsciiFileString(buffer);
	names.Insert( numID, fileName );
}

const gchar* GetFullEffectName(gtuint uiIndex);