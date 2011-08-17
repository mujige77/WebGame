//
//  GnITabPage.h
//  Core
//
//  Created by Max Yoon on 11. 7. 22..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GnITabPage__
#define __Core__GnITabPage__

#include "GnInterfaceGroup.h"

class GnITabPage : public GnInterfaceGroup
{
	GnDeclareRTTI;
private:
	gtuint mNumTabPage;
	
public:
	GnITabPage(const gchar* pcBackgroundName = NULL);
	virtual ~GnITabPage(){}
	
	void SetBackground(const gchar* pcBackgroundName);
public:
	inline gtuint GetNumTabPage() {
		return mNumTabPage;
	}
	inline void SetNumTabPage(gtuint uiNum) {
		mNumTabPage = uiNum;
	}
//	virtual void AddChild(GnInterface* pChild)
//	{
//		GnInterfaceGroup::AddChild( pChild );
//		GetParentUseNode()->addChild( pChild->GetParentUseNode() );
//	}
};
GnSmartPointer(GnITabPage);
#endif
