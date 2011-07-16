//
//  GActionDamage.h
//  Core
//
//  Created by Max Yoon on 11. 7. 13..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GActionDamage__
#define __Core__GActionDamage__

#include "GAction.h"

class GActionDamage : public GAction
{
private:
	GLayer* mpActorLayer;
	gint mEffectIndex;
	Gn2DMeshObject* mpMeshObject;
	bool mIsMeshAddToParent;
	
public:
	GActionDamage(GActorController* pController);
	virtual ~ GActionDamage();
	
public:
	void Update(float fTime);
	void AttachActionToController();
	inline gtint GetActionType() {
		return ACTION_DAMAGE;
	}
	inline void DetachActionToController() {
		if( mpMeshObject && mpMeshObject->GetMesh()->getParent() )
			GetActorLayer()->RemoveChild( mpMeshObject );
	};
public:
	inline void SetActorLayer(GLayer* pActorLayer) {
		mpActorLayer = pActorLayer;
	}
	inline gint GetEffectIndex() {
		return mEffectIndex;
	}
	inline void SetEffectIndex(gint uiIndex) {
		mEffectIndex = uiIndex;
	}

protected:
	void SetEffectIndexDamage();
	
protected:
	inline GLayer* GetActorLayer() {
		return mpActorLayer;
	}
	inline void RemoveMeshParent() {
		if( mpMeshObject && mpMeshObject->GetMesh()->getParent() )
			GetActorLayer()->RemoveChild( mpMeshObject );
	}
};

#endif
