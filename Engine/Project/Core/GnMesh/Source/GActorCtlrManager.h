//
//  GActorCtlrManager.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GActorCtlrManager__
#define __HiroCat__GActorCtlrManager__

#include "GActorController.h"

class GActorInfoDatabase;
class GActorCtlrManager : public GnMemoryObject
{
	GnTPrimitiveArray<GActorController*> mActors;
	GnTPrimitiveArray<gtuint> mActorIDs;
	GLayer* mpActorLayer;

protected:
	static const gtuint msNumAttackLine = 2;
	
public:
	GActorCtlrManager(GLayer* pLayer);
	virtual ~GActorCtlrManager();
	//void SetStartPostion(GActorController* pActorController, gtuint uiDirection, gtuint uiAttackLine);
	
public:
	virtual void Update(float fDeltaTime);
	virtual void CollisionCheck(GActorCtlrManager* pCheckCtlrManager);
					   
public:
	inline void AddActorCtlr(GActorController* pActorCtlr) {
		GetActorLayer()->AddChild( pActorCtlr->GetMesh()
			, GetGameState()->GetGameHeight() - pActorCtlr->GetPosition().y );
		mActors.Add( pActorCtlr );
	};
	inline GActorController* GetActorCtlr(gtuint uiIndex)	{
		return mActors.GetAt( uiIndex );
	}
	inline gtuint GetActorCtlrSize() {
		return mActors.GetSize();
	}
	inline void AddEnableActorIndex(gtuint uiIndex) {
		mActorIDs.Add( uiIndex );
	};
	inline gtuint GetActorIndex(gtuint uiIndex) {
		return mActorIDs.GetAt( uiIndex );
	}
	inline gtuint GetActorIndexSize() {
		return mActorIDs.GetSize();
	}
	inline GLayer* GetActorLayer() {
		return mpActorLayer;
	}
};

#endif
