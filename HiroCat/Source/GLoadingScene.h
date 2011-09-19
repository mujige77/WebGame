//
//  GLoadingScene.h
//  HiroCat
//
//  Created by Max Yoon on 11. 9. 3..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef HiroCat_GLoadingScene_h
#define HiroCat_GLoadingScene_h

class GLoadingLayer : public GLayer
{
public:
	static GLoadingLayer* CreateLoadingLayer(guint32 uiLoadingBgIndex);
};
class GLoadingScene : public GScene
{	
public:
	static GLoadingScene* CreateLoadingScene();

public:
	const gchar* GetSceneName() {
		return GScene::SCENENAME_LOADING;
	}
};

#endif
