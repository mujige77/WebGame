#ifndef __Core__GnInterfaceGroup__
#define __Core__GnInterfaceGroup__

class GnInterfaceGroup : public GnInterface
{	
	GnDeclareRTTI;
private:
	GnSignal2<GnInterface*, GnIInputEvent*> mSignal;
	GnTObjectArray<GnInterfacePtr> mChildren;
	GnTObjectArray<GnInterfacePtr> mPersonalChildren; // Personal Push Check
	bool mAllPush;
	
public:
	GnInterfaceGroup();
	virtual ~GnInterfaceGroup();
public:
	bool PushUp(float fPointX, float fPointY);
	bool PushMove(float fPointX, float fPointY);
	void PushUpPersonalChildren(float fPointX, float fPointY);
	void PushUp();	
	void Update(float fDeltaTime);	

	virtual bool Push(float fPointX, float fPointY);
	virtual void SetAlpha(guchar ucAlpha);
	virtual void SetPosition(GnVector2& cPos);
	
	virtual void AddChild(GnInterface* pChild)
	{
		mChildren.Add( pChild );
		GetParentUseNode()->addChild( pChild->GetParentUseNode() );
	}
	virtual void AddChild(GnInterface* pChild, gint32 iZorder)
	{
		mChildren.Add( pChild );
		GetParentUseNode()->addChild( pChild->GetParentUseNode(), iZorder );
	}
	virtual void RemoveChild(GnInterface* pChild)
	{
		GnInterfacePtr ptrChild = pChild;
		GetParentUseNode()->removeChild( ptrChild->GetParentUseNode(), true );
		mPersonalChildren.RemoveAndFill( ptrChild );
		mChildren.RemoveAndFill( ptrChild );
	}
	virtual gtuint GetChildrenSize() {
		return mChildren.GetSize();
	}
	virtual GnInterface* GetChild(gtuint uiIndex) {
		return mChildren.GetAt( uiIndex );
	}	
	virtual inline GnInterface* GetChildFromTegID(gint32 iID) {
		for ( gtuint i = 0 ; i < GetChildrenSize(); i++ )
		{
			GnInterface* child = GetChild( i );
			if( child->GetTegID() == iID )
				return child;
		}
		return NULL;
	}
	virtual inline void SubscribeClickedEvent(GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot) {
		mSignal.Subscribe( pSlot );
	}
	
public:
	inline void AddPersonalChild(GnInterface* pChild) {
		mPersonalChildren.Add( pChild );
	}
	inline void SetIsAllPush(bool val) {
		mAllPush = val;
	}
protected:
	bool PushChild(GnInterface* pChild, float fPointX, float fPointY);
};

#endif
