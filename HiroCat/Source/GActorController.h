//
//  GActorController.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GActorController__
#define __HiroCat__GActorController__
#include "GCPMove.h"
class GActorController : public GnMemoryObject
{
	GnDeclareFlags( guint32 );
	enum
	{
		MASK_DESTORY = 0x00000001,
	};
public:
	GCPMove mMoveCom;
	
protected:
	Gn2DActorPtr mpsActor;
	
public:
	GActorController();
	void Update(float fDeltaTime);
	
	inline bool IsDestory() {
		return GetBit( MASK_DESTORY );
	};
	inline void SetIsDestory(bool val) {
		SetBit( val, MASK_DESTORY );
	};
	inline Gn2DActor* GetActor() {
		return mpsActor;
	}
	inline Gn2DMeshObject* GetMesh() {
		return mpsActor->GetRootNode();
	}
	 
protected:
	bool LoadActor(const gchar* pcFilePath);
};

#endif
