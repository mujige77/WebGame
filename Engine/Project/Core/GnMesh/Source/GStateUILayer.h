//
//  GStateUILayer.h
//  Core
//
//  Created by Max Yoon on 11. 7. 30..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GStateUILayer_h
#define Core_GStateUILayer_h

#include "GInterfaceLayer.h"

class GnITabCtrl;
class GStateUILayer : public GInterfaceLayer
{
private:
	GnITabCtrl* mpTabCtrl;
	
public:
	GStateUILayer();
	virtual ~GStateUILayer();
	virtual GnInterfaceGroup* CreateInterface(gtuint uiIndex
		, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot);	
	
protected:
	GnInterfaceGroup* CreateMenu();
	GnInterfaceGroup* CreateOtherUI();
	
};

#endif
