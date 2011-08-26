//
//  GDialog.h
//  Core
//
//  Created by Max Yoon on 11. 8. 21..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GDialog_h
#define Core_GDialog_h

class GDialog : public GnSmartObject
{
protected:
	GnInterfacePtr mpsDialogInterface;
	CCLayerColor* mpDialogColorLayer;
	GLayer* mpDialogLayer;

public:
	static GDialog* CreateModalColor(GnInterface* pDlgInterface, const guchar ucR = 0, const guchar ucG = 0
		, const guchar ucB = 0, const guchar ucA = 128);
	
public:	
	gint Show();
	void Close();

public:
	inline GnInterface* GetDialogInterface() {
		return mpsDialogInterface;
	}
	inline GLayer* GetDialogLayer() {
		return mpDialogLayer;
	}
	
protected:
	GDialog(GnInterface* pInterface, GLayer* pLayer);
	void SetDialogColorLayer(CCLayerColor* pColorLayer) {
		mpDialogColorLayer = pColorLayer;
	};
};

GnSmartPointer(GDialog);

#endif
