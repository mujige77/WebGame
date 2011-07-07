#ifndef __Core__GnInterface__
#define __Core__GnInterface__

class GnInterface : public GnSmartObject
{
	GnDeclareFlags(guint32);
	enum
	{
		MASK_PUSH = 0x000001,
		MASK_HOVER = 0x000002,
		MASK_DISABLE = 0x000004,
		MASK_CANTPUSH = 0x000008, 
	};
	
protected:
	GnFRect mRect;
	GnVector2 mPosition;
	GnInterfaceNode mParentUseNode;
	
public:
	GnInterface();
	
public:
	virtual bool Push(float fPointX, float fPointY);
	virtual void Pushup(float fPointX, float fPointY);
	
public:
	virtual inline void AddChild(GnInterface* pChild) {}
	virtual inline void Update(float fDeltaTime) {}
	virtual inline gtuint GetChildrenSize() {
		return 0;
	}
	inline virtual GnInterface* GetChild(gtuint uiIndex) {
		return NULL;
	}
	virtual inline void SetIsCantPush(bool val) {
		SetBit( val, MASK_CANTPUSH );
	}
	virtual inline void SetIsDisable(bool val) {
		SetBit( val, MASK_DISABLE );
	}
public:
	inline GnInterfaceNode* GetParentUseNode()
	{
		return &mParentUseNode;
	}
	inline bool IsPush() {
		return GetBit( MASK_PUSH );
	}
	inline void SetIsPush(bool val) {
		SetBit( val, MASK_PUSH );
	}
	inline bool IsHover() {
		return GetBit( MASK_HOVER );
	}
	inline void SetIsHover(bool val) {
		SetBit( val, MASK_HOVER );
	}
	inline bool IsCantPush() {
		return GetBit( MASK_CANTPUSH );
	}
	inline bool IsDisable() {
		return GetBit( MASK_DISABLE );
	}	
	inline GnFRect& GetRect() {
		return mRect;
	}
	inline void SetRect(GnFRect& rect ) {
		mRect = rect;
	};
	inline void SetRect(float fLeft, float fTop, float fRight, float fBottom) {
		mRect.left = fLeft;
		mRect.top = fTop;
		mRect.right = fRight;
		mRect.bottom = fBottom;
	};
	inline GnVector2& GetPosition() {
		return mPosition;
	}
	inline void SetUIPoint(float fPointX, float fPointY)
	{
		CCSize size = GetParentUseNode()->getContentSize();
		size.width /= 2;
		size.height /= 2;
		mPosition.x = fPointX + size.width;
		mPosition.y = GetGameState()->GetGameHeight() - fPointY - size.height;
		SetPosition( mPosition );
	}
	inline GnVector2 GetContentSize() {
		CCSize size = GetParentUseNode()->getContentSize();
		GnVector2 ret( size.width, size.height );
		return ret;
	}
	
protected:
	virtual void SetPosition(GnVector2& cPos) = 0;
	
protected:
	inline void SetContentSize(float fWidth, float fHeight) {
		GetParentUseNode()->setContentSize( CCSizeMake( fWidth, fHeight ) );
	}
};

GnSmartPointer(GnInterface);
#endif
