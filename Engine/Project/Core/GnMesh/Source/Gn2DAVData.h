#ifndef GN2DAVOBJECT_H
#define GN2DAVOBJECT_H

class Gn2DAVData : public GnObject
{
	GnDeclareRTTI;
	GnDeclareStream;
	GnDeclareFlags( gushort );
public:
	enum 
	{
		MASK_MESHSTREAM = 0x000001,
		//COLLISION_RECT = 0x000002,
	};
	class CollisionRect : public GnMemoryObject
	{
	public:
		CollisionRect(){};
		CollisionRect(gint32 type, GnFRect rect)
		{
			mType = type;
			mRect = rect;
		}
	public:
		gint32 mType;
		GnFRect mRect;
	};

protected:
	GnVector2 mAnchorPoint;
	GnTObjectArray<CollisionRect> mCollisionRects;
	GnTObjectArray<CollisionRect> mOriginalCollisionRects;
	
public:
	Gn2DAVData();
	virtual ~Gn2DAVData(){};
	void Move(GnVector2& movePoint);
	void FlipX(bool bFlip, float postionX);

	inline GnVector2& GetAnchorPoint() {
		return mAnchorPoint;
	}
	inline void SetAnchorPoint(GnVector2& val) {
		mAnchorPoint = val;
	}
	inline gtuint GetCollisionCount() {
		return mCollisionRects.GetSize();
	}
	inline void AddCollisionRect(gint32 uiID, GnFRect& val)
	{
		mCollisionRects.Add( CollisionRect( uiID, val ) );
	}
	inline void SetCollisionRect(gtuint uiIndex, gint32 uiID, GnFRect& val)
	{
		mCollisionRects.SetAt( uiIndex, CollisionRect( uiID, val ) );
	}
	inline CollisionRect& GetCollisionRect(gtuint uiIndex) {
		return mCollisionRects.GetAt( uiIndex );
	}
	inline void RemoveAllCollisionRect() {
		mCollisionRects.RemoveAll();
	}

	inline bool IsMeshStream() {
		return GetBit( MASK_MESHSTREAM );
	}
	inline void SetMeshStream(bool val) {
		SetBit( val, MASK_MESHSTREAM );
	}

	// 툴 때문에 만든 것임
public:
	inline GnTObjectArray<CollisionRect>* GetCollisionRects() {
		return &mCollisionRects;
	}

	//inline GnIRect GetAttackRect() {
	//	return mAttackRect;
	//}
	//inline void SetAttackRect(GnIRect val) {
	//	mAttackRect = val;
	//}
	//inline bool IsExistCollision() {
	//	return GetBit( COLLISION_RECT );
	//}
	//inline void SetExistCollision(bool val) {
	//	SetBit( val, COLLISION_RECT );
	//}	
	//inline bool IsExistAttack() {
	//	return GetBit( ATTACK_RECT );
	//}
	//inline void SetExistAttack(bool val) {
	//	SetBit( val, ATTACK_RECT );
	//}
};

GnSmartPointer(Gn2DAVData);

#endif // GN2DAVOBJECT_H