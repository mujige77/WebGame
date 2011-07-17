#ifndef __Core__GnInterfaceGroup__
#define __Core__GnInterfaceGroup__

class GnInterfaceGroup : public GnInterface
{	
private:
	GnSignal2<GnInterface*, GnIInputEvent*> mSignal;
	GnTObjectArray<GnInterfacePtr> mChildren;
	
public:
	bool Push(float fPointX, float fPointY);
	bool Pushup(float fPointX, float fPointY);
	bool PushMove(float fPointX, float fPointY);
	void PushUp();
	void Update(float fDeltaTime);
	
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
