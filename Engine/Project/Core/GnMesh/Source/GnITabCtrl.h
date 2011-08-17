//
//  GnITabCtrl.h
//  Core
//
//  Created by Max Yoon on 11. 7. 22..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GnITabCtrl__
#define __Core__GnITabCtrl__
#include "GnITabPage.h"

class GnIButton;
class GnITabCtrl : public GnInterfaceGroup
{
protected:
	GnInterfaceGroup* mpTabButtons;
	GnTPrimitiveSet<GnITabPage*> mTabPages;
	GnSignal2<gtuint, GnITabPage*> mSignal;
	GnMemberSlot2<GnITabCtrl, GnInterface*, GnIInputEvent*> mTabButtonPushEvent;
	gtint mNumActiveTab;
	GnVector2 mDefaultButtonSize;
	GnTPrimitiveSet< GnBaseSlot2< GnInterface*, GnIInputEvent*>* > mSignalSet;
	
public:
	static GnITabCtrl* CreateTabCtrl(const gchar* pcBackgroundImage, float fSizeX, float fSizeY);
	static GnITabCtrl* CreateTabCtrl(float fTabBackgroundSizeX, float fTabBackgroundSizeY
		, float fTabButtonSizeX, float fTabButtonSizeY);

public:
	void AddTabCreateButtonImage(GnITabPage* pTabPage, const gchar* pcDefaultButtonImage
		, const gchar* pcClickButtonImage);	
	void SetActiveTab(gtint iNumActive);
	
public:
	void SetPosition(GnVector2& cPos);
	void SetRect(float fLeft, float fTop, float fRight, float fBottom);
	void SubscribeClickedEvent(GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot);
	
public:
	inline gint GetNumActiveTab() {
		return mNumActiveTab;
	}
	inline GnITabPage* GetActiveTabPage() {
		if( mNumActiveTab != -1 )
			return mTabPages.GetAt( (gtuint)mNumActiveTab );
		return NULL;
	}
	inline GnITabPage* GetTabPage(gtuint uiIndex) {
		if( mTabPages.GetSize() < uiIndex )
			return NULL;
		return mTabPages.GetAt( uiIndex );
	}

protected:
	GnVector2 GetStartTabButtonPosition();
	void SetTabButtonPosition(GnVector2 cStartPos);
	void PushTabButton(GnInterface* pInterface, GnIInputEvent* pEvent);
	
protected:
	GnITabCtrl(Gn2DMeshObject* pcBackgroundMesh);	
};

#endif
