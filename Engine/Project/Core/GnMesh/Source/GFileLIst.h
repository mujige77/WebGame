//
//  GFileLIst.h
//  Core
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GFileLIst__
#define __Core__GFileLIst__

class GFileList : public GnMemoryObject
{
	static GFileList* mpSingleton;
	GnTPrimitiveDeleteMap<gtuint, gchar*> mEnemyNames;
	GnTPrimitiveDeleteMap<gtuint, gchar*> mForcesNames;
	
public:
	GFileList();
	static GFileList* GetSingleton();
	static GnMemoryObject* Create();
	
	bool LoadFile(const gchar* pcFilePath);
	const gchar* GetEnemyFileName(gtuint uiIndex) {
		gchar* name = NULL;
		mEnemyNames.GetAt(uiIndex, name);
		return name;
	};
	const gchar* GetForcesFileName(gtuint uiIndex)
	{
		gchar* name = NULL;
		mEnemyNames.GetAt(uiIndex, name);
		return name;
	};	
	
private:
	void ReadList(GnFile* pFile, const gchar* firstName, GnTPrimitiveDeleteMap<gtuint, gchar*>& names);
	void AddListFromFile(gchar* buffer, GnTPrimitiveDeleteMap<gtuint, gchar*>& names);
};

#define GetFileList GFileList::GetSingleton

#endif
