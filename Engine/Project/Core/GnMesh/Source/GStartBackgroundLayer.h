//
//  GStartBackgroundLayer.h
//  Core
//
//  Created by Max Yoon on 11. 7. 25..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GStartBackgroundLayer_h
#define Core_GStartBackgroundLayer_h

class GStartBackgroundLayer : public GLayer
{
	enum
	{
		NUM_CLOUD = 5,
	};
private:
	GnReal2DMesh* mpBackground;
	GnReal2DMesh* mpCloudsMeshs[NUM_CLOUD];
	
public:
	static GStartBackgroundLayer* CreateBackground();
	void CloudActionCallback(CCNode* pSender);
protected:
	bool InitBackground();
	bool InitClouds();
};

#endif
