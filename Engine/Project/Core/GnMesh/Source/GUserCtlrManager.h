//
//  GUserCtlrManager.h
//  Core
//
//  Created by Max Yoon on 11. 6. 26..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GUserCtlrManager__
#define __Core__GUserCtlrManager__

#include "GActorCtlrManager.h"

class GnIButton;
class GUserCtlrManager : public GActorCtlrManager
{
	static const gtuint NUM_BUTTON = 4;

private:
	GLayer* mpInterfaceLayer;
	GActorController* mpUserCtlr;
	GnIButton* mButtons[NUM_BUTTON];
	GnMemberSlot2<GUserCtlrManager, GnInterface*, GnIInputEvent*> mMoveInputEvent;
	
public:
	GUserCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer);
	virtual ~GUserCtlrManager();
	
public:
	void Update(float fDeltaTime);
	void Init();
	void Move(GnInterface* pInterface, GnIInputEvent* pEvent);
	
protected:
	void UpdateBackgroundLayer();

};

#endif
