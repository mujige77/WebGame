//
//  GGameManager.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GGameManager__
#define __HiroCat__GGameManager__

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
//	static GGameManager* mpSingleton;
	GActorCtlrManager* mActorManage[MAX_CTLRMANAGER];

public:
//	static GGameManager* GetSingleton();
//	static GnMemoryObject* Create();
	
	GGameManager(GnLayer* pLayer);
	void Update(float fTime);

};

#endif
