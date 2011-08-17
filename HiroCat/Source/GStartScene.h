//
//  GStartScene.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 13..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GStartScene__
#define __HiroCat__GStartScene__

class GnITabCtrl;
class GStartScene : public GScene
{
	enum
	{
		MAX_PLAYER = 3,
	};
private:
	GLayer* mpInterfaceLayer;
	GLayer* mpBackgroundLayer;
	GnITabCtrl* mpTab;
	GnMemberSlot2<GStartScene, GnInterface*, GnIInputEvent*> mInputEvent;
	
public:
	GStartScene();
	virtual ~GStartScene();
	
public:
	static GStartScene* CreateStartScene();
	bool CreateInterface();
	bool CreateBackground();
	
public:
	virtual const gchar* GetSceneName();
	
protected:
	void InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
	
private:
	void InputSelectModeTabButton(gtuint uiNumButton);
	void InputLoadTabButton(gtuint uiNumButton);
	void SetSelectModeTabButton();
};

#endif
