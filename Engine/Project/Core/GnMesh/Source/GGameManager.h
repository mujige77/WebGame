#ifndef __HiroCat__GGameManager__
#define __HiroCat__GGameManager__

#include "GActorInfoDatabase.h"
class GActorCtlrManager;
class GGameManager : public GnMemoryObject
{
public:
	enum eManagerType
	{
		ENEMY_CTLRMANAGER,
		MAX_CTLRMANAGER,
	};
	
private:
	GActorInfoDatabase mActorInfoDatabase;
//	static GGameManager* mpSingleton;
	GActorCtlrManager* mActorManage[MAX_CTLRMANAGER];

public:
//	static GGameManager* GetSingleton();
//	static GnMemoryObject* Create();
	
	GGameManager(GnLayer* pLayer);
	void Update(float fTime);

};

#endif
