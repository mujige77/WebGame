#ifndef GTTOOLSETTINGS_H
#define GTTOOLSETTINGS_H

class GtToolSettings
{
private:
	static gchar mWorkPath[GN_MAX_PATH];
	static gchar mBackgroundFile[GN_MAX_PATH];	

public:
	static void EBMStartup();
	static void EBMShutdown();
	static void SetWorkPath(const char* path);
	static gchar* GetWorkPath();
	static void  SetBackgroundFilePath(const char* pcPath);
	static gchar* GetBackgroundFilePath();

	static void MakeSaveFilePath(const gchar* pcFileName, const gchar* pcFolder, char* outPath, gsize outSize);
	static void CreateWorkDirectory();
	static void CreateDirectoryInWorkDirectory(const gchar* pcFolderName);	
	static void SaveFile();
	static void LoadFile();	
};

#endif // GTTOOLSETTINGS_H
