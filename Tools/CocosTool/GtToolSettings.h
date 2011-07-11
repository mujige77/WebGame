#ifndef GTTOOLSETTINGS_H
#define GTTOOLSETTINGS_H

class GtToolSettings
{
private:
	static gchar mWorkPath[GN_MAX_PATH];
	static gchar mBackgroundFile[GN_MAX_PATH];	
	static gint32 mScalePercent;

public:
	static void EBMStartup();
	static void EBMShutdown();
	static void SetWorkPath(const char* path);
	static gchar* GetWorkPath();
	static void  SetBackgroundFilePath(const char* pcPath);
	static gchar* GetBackgroundFilePath();
	static gint32 GetScalePercent();
	static void SetScalsePercent(gint32 iScale);
	static float GetScale();

	static void MakeSaveFilePath(const gchar* pcFileName, const gchar* pcFolder, char* outPath
		, gsize outSize);
	static void CreateWorkDirectory();
	static void CreateDirectoryInWorkDirectory(const gchar* objectType, const gchar* pcFolderName);	
	static void SaveFile();
	static void LoadFile();	
};

#endif // GTTOOLSETTINGS_H
