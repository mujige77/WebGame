//
//  GFileList.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnMeshPCH.h"
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
	std::string fileName = GetFullPath( "template.lst", "./" );
	GnVerify( LoadFile( fileName.c_str() ) );
}

bool GFileList::LoadFile(const gchar *pcFilePath)
{
	GnFile* file = GnFile::GetFile( pcFilePath, GnFile::READ_ACSII, 256 );
	if( file == NULL )
		return false;	
		
	ReadList( file, "ForcesList", mForcesNames );
	ReadList( file, "EnemyList", mEnemyNames );
	file->Destory();
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
	sscanf( buffer, "%c%d", tempString, &numID );
	
	size_t len = GnStrlen( buffer );
	gchar* fileName = GnAlloc(gchar, len+4);
	strcpy( fileName, buffer );
	fileName[len-1] = '\0';
	//GnStrcat(fileName, ".gat", len);
	names.Insert( numID, fileName );
}