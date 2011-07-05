//
//  GnInterfaceGroup.h
//  Core
//
//  Created by Max Yoon on 11. 6. 28..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GnInterfaceGroup__
#define __Core__GnInterfaceGroup__

class GnInterfaceGroup : public GnInterface
{	
private:
	GnSignal2<GnInterface*, GnIInputEvent*> mSignal;
	GnTObjectArray<GnInterfacePtr> mChildren;
	
public:
	virtual bool Push(float fPointX, float fPointY);
	virtual void Pushup(float fPointX, float fPointY);
	virtual void AddChild(GnInterface* pChild)
	{
		mChildren.Add( pChild );
	}
	virtual gtuint GetChildrenSize() {
		return mChildren.GetSize();
	}
	virtual GnInterface* GetChild(gtuint uiIndex) {
		return mChildren.GetAt( uiIndex );
	}
	
public:
	inline void SubscribeClickedEvent(GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot) {
		mSignal.Subscribe( pSlot );
	}
protected:
	virtual void SetPosition(GnVector2& cPos);
};

#endif
