//
//  GStartInterfaceLayer.h
//  Core
//
//  Created by Max Yoon on 11. 7. 25..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GStartInterfaceLayer_h
#define Core_GStartInterfaceLayer_h

#include "GInterfaceLayer.h"

class GnITabCtrl;
class GStartInterfaceLayer : public GInterfaceLayer
{
private:
	GnITabCtrl* mpTabCtrl;

public:
	GStartInterfaceLayer();
	virtual ~GStartInterfaceLayer();
	virtual GnInterfaceGroup* CreateInterface(gtuint uiIndex
		, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot);	

protected:
	GnInterfaceGroup* CreateMenu();
	
};

#endif
