#ifndef GNSCENEMANAGER_H
#define GNSCENEMANAGER_H

class GnLayer;

class GnSceneManager
{
private:
	static GnSceneManager* mpSingleton;
	GnCocosScene	* mpMain;

public:
	GnSceneManager();
	virtual ~GnSceneManager();
	static void _StartupEBM();
	static void _ShutdownEBM();
	static GnSceneManager* GetSingleton();
	
	GnCocosScene* GetMainGameScene();
	GnLayer* GetMainGameLayer();

protected:
		GnCocosScene* CreateMainGameScene();
};

#define GetSceneManager GnSceneManager::GetSingleton

#endif // GNSCENEMANAGER_H
