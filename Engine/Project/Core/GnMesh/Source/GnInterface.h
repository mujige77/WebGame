#ifndef __Core__GnInterface__
#define __Core__GnInterface__

class GnInterface : public GnSmartObject
{
	GnDeclareFlags(guint32);
	enum
	{
		MASK_HOVER = 0x000001,
		MASK_DISABLE = 0x000002,
		MASK_CANTPUSH = 0x000004, 
		MASK_ENABLEPUSHMOVE = 0x000008,
	};
	
protected:
	GnFRect mRect;
	GnVector2 mPosition;
	GnInterfaceNode mParentUseNode;
	gtuint mPushCount;
	Gn2DMeshObjectPtr mpsDefaultMesh;
	
public:
	GnInterface();
	bool CreateDefaultImage(const gchar* pcImageName);
	
public:
	virtual bool Push(float fPointX, float fPointY);
	virtual bool Pushup(float fPointX, float fPointY);
	virtual bool PushMove(float fPointX, float fPointY);
	virtual void PushUp();
	
	virtual inline void AddChild(GnInterface* pChild) {}
	virtual inline void Update(float fDeltaTime) {}
	virtual inline gtuint GetChildrenSize() {
		return 0;
	}
	virtual inline GnInterface* GetChild(gtuint uiIndex) {
		return NULL;
	}
	virtual inline void SetIsCantPush(bool val) {
		SetBit( val, MASK_CANTPUSH );
	}
	virtual inline void SetIsDisable(bool val) {
		SetBit( val, MASK_DISABLE );
	}
public:
	GNFORCEINLINE bool IfUseCheckCollision(float fPointX, float fPointY)
	{
		if( IsDisable() || IsCantPush() )
			return false;	
		
		if( mRect.ContainsPoint(fPointX, fPointY) == false )
			return false;
		
		return true;
	}
	inline GnInterfaceNode* GetParentUseNode()
	{
		return &mParentUseNode;
	}
	inline bool IsPush() {
		return GetPushCount() != 0;
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
	inline bool IsEnablePushMove() {
		return GetBit( MASK_ENABLEPUSHMOVE );
	}
	inline void SetIsEnablePushMove(bool val) {
		SetBit( val, MASK_ENABLEPUSHMOVE );
	}
	inline gtuint GetPushCount() {
		return mPushCount;
	}
	inline gtuint AddPushCount() {
		return ++mPushCount;
	}
	inline gtuint SubPushCount() {
		if( mPushCount > 0 )
			--mPushCount;
		return mPushCount;
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
	void AddMeshToParentNode(Gn2DMeshObject* pChild);
	void AddToParentNode(GnInterfaceNode* pNode);
protected:
	virtual inline void SetPosition(GnVector2& cPos) {
		if( mpsDefaultMesh )
			mpsDefaultMesh->SetPosition( cPos );
	};
	
protected:
	inline void SetContentSize(float fWidth, float fHeight) {
		GetParentUseNode()->setContentSize( CCSizeMake( fWidth, fHeight ) );
	}
};

GnSmartPointer(GnInterface);
#endif
