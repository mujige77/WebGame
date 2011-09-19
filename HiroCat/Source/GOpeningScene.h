//
//  GOpeningScene.h
//  HiroCat
//
//  Created by Max Yoon on 11. 9. 3..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef HiroCat_GOpeningScene_h
#define HiroCat_GOpeningScene_h

class GOpeningLayer : public GLayer
{
private:
	GnMemberSlot2<GOpeningLayer, GnInterface*, GnIInputEvent*> mInputEvent;
	gtuint mCurrentPage;
	
public:
	static GOpeningLayer* CreateOpeningLayer(gtuint uiPage);
	
private:
	GOpeningLayer();
	void InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
};

class GOpeningScene : public GScene
{
public:
	static CCScene* CreateLoadingScene(gtuint uiPage);
	
public:
	const gchar* GetSceneName() {
		return GScene::SCENENAME_OPENING;
	}
};


#endif
