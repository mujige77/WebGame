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

class GActorCtlrManager : public GnMemoryObject
{
	GnTPrimitiveArray<GActorController*> mActors;
	GnTPrimitiveArray<gtuint> mActorIDs;
	GLayer* mpActorLayer;
	GnVector2 mStartActorPostion;
	
public:
	GActorCtlrManager(GLayer* pLayer);
	virtual ~GActorCtlrManager();
	virtual void Update(float fDeltaTime);
	void SetStartPostion(GActorController* pActorController, gtuint uiAttackLine);
					   
public:
	inline void AddActorCtlr(GActorController* pActorCtlr) {
		GetActorLayer()->AddChild( pActorCtlr->GetMesh(), 1 );
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
	inline GnVector2& GetStartActorPostion() {
		return mStartActorPostion;
	}
	inline void SetStartActorPostion(float fPostionX, float fPostionY) {
		mStartActorPostion.x = fPostionX;
		mStartActorPostion.y = fPostionY;
	}
};

#endif
