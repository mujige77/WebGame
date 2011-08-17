#ifndef __Core__GFileLIst__
#define __Core__GFileLIst__

class GFileList : public GnMemoryObject
{
private:
	GnDeclareSingleton(GFileList);
	GnTPrimitiveDeleteMap<gtuint, gchar*> mEnemyNames;
	GnTPrimitiveDeleteMap<gtuint, gchar*> mForcesNames;
	GnTPrimitiveDeleteMap<gtuint, gchar*> mEffectNames;
	
public:
	GFileList();
	~GFileList();
//	static GFileList* GetSingleton();
//	static GnMemoryObject* Create();
	
public:
	bool LoadFile(const gchar* pcFilePath);
	bool GetFullEffectName(gtuint uiIndex, gstring& outString);
	
public:
	const gchar* GetEnemyFileName(gtuint uiIndex) {
		gchar* name = NULL;
		mEnemyNames.GetAt(uiIndex, name);
		return name;
	};
	const gchar* GetForcesFileName(gtuint uiIndex)
	{
		gchar* name = NULL;
		mForcesNames.GetAt(uiIndex, name);
		return name;
	};
	const gchar* GetEffectName(gtuint uiIndex)
	{
		gchar* name = NULL;
		mEffectNames.GetAt(uiIndex, name);
		return name;		
	}	
	void GetForcesFileName(gtuint uiIndex, gchar* pcOutName, gsize uiOutSize)
	{
		GnSprintf( pcOutName, uiOutSize, "C%d", uiIndex );
	}
private:
	void ReadList(GnFile* pFile, const gchar* firstName, GnTPrimitiveDeleteMap<gtuint, gchar*>& names);
	void AddListFromFile(gchar* buffer, GnTPrimitiveDeleteMap<gtuint, gchar*>& names);
};


#define GetFileList GFileList::GetSingleton

#endif
