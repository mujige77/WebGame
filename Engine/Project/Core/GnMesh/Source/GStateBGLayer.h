//
//  GStateBGLayer.h
//  Core
//
//  Created by Max Yoon on 11. 7. 30..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GStateBGLayer_h
#define Core_GStateBGLayer_h

class GStateBGLayer : public GLayer
{
public:
	static GStateBGLayer* CreateBackground();
	
public:
	bool InitBackground();
};

#endif
