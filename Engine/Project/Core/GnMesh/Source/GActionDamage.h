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
#include "GAttackDamageInfo.h"

class GnIProgressBar;
class GActionDamage : public GAction
{
private:
	GLayer* mpActorLayer;
	gint mEffectIndex;
	Gn2DMeshObjectPtr mpsMeshObject;
	bool mIsMeshAddToParent;
	GAttackDamageInfo mAttackDamage;
	
public:
	GActionDamage(GActorController* pController);
	virtual ~ GActionDamage();
	GnVector2ExtraData* CreateDamageEffect();
	
public:
	void Update(float fTime);
	void AttachActionToController();
	inline gtint GetActionType() {
		return ACTION_DAMAGE;
	}
	inline void DetachActionToController() {
		if( mpsMeshObject && mpsMeshObject->GetMesh()->getParent() )
			GetActorLayer()->RemoveChild( mpsMeshObject );
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
	void SetAttackDamage(GAttackDamageInfo& cInfo);
	GAttackDamageInfo* GetAttackDamageInfo() {
		return &mAttackDamage;
	}
	
protected:
	inline GLayer* GetActorLayer() {
		return mpActorLayer;
	}
	inline void RemoveMeshParent() {
		if( mpsMeshObject && mpsMeshObject->GetMesh()->getParent() )
			GetActorLayer()->RemoveChild( mpsMeshObject );
	}
};

#endif
