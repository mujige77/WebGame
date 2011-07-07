#ifndef __HiroCat__GActorController__
#define __HiroCat__GActorController__

#include "GCurrentActorInfo.h"

class GInfo;
class GAction;

class GActorController : public GnMemoryObject
{
	GnDeclareFlags( guint32 );
	enum
	{
		MASK_DESTORY = 0x00000001,
	};
	
protected:
	Gn2DActorPtr mpsActor;
	GnTPrimitiveArray<GInfo*> mInfoComponents;
	GnTPrimitiveArray<GAction*> mActionComponents;
	GnTPrimitiveArray<GAction*> mCurrentActions;
	
private:
	GCurrentActorInfo mCurrentInfo;
	GnVector2 mStrides;
	GnVector2 mMovePosition;
	
	
protected:
	static void GetFullActorFilePath(const gchar* pcID, gstring& pcOutPath);
	
public:
	GActorController();
	virtual ~GActorController();
	bool Init(const gchar* pcActorFilePath, const gchar* pcID, guint32 uiLevel);
	void Update(float fDeltaTime);
	void RemoveAllInfoComponets();
	void RemoveAllActionComponets();
	bool IsEnableMove();
	void AddCurrentAction(GAction* pComponent);
	void ReceiveAttack(GActorController* pFromActor);
		
public:
	virtual inline void SetPosition(GnVector2& pos) {
		GetMesh()->SetPosition( pos );
	};
	virtual void Start();

	
public:
	inline void RemoveAllCurrentComponets() {
		mCurrentActions.RemoveAll();
	}
	inline void RemoveCurrentComponent(gtuint uiIndex) {
		mCurrentActions.SetAt( uiIndex, NULL );
	}
	inline gtuint GetCurrentActionCount() {
		return mCurrentActions.GetSize();
	}
	inline GAction* GetCurrentAction(gtuint uiIndex) {
		return mCurrentActions.GetAt( uiIndex );
	}
	inline bool IsDestory() {
		return GetBit( MASK_DESTORY );
	};
	inline void SetIsDestory(bool val) {
		SetBit( val, MASK_DESTORY );
	};
	inline Gn2DActor* GetActor() {
		return mpsActor;
	}
	inline Gn2DMeshObject* GetMesh() {
		return mpsActor->GetRootNode();
	}
	inline GnVector2& GetPosition() {
		return GetMesh()->GetPosition();
	}
	inline GInfo* GetInfoComponent(gtuint uiIndex) {
		return mInfoComponents.GetAt( uiIndex );
	}
	inline GAction* GetActionComponent(gtuint uiIndex) {
		return mActionComponents.GetAt( uiIndex );
	}
	inline GnVector2& GetMovePosition() {
		return mMovePosition;
	}
	inline void SetMovePosition(GnVector2& cPosition) {
		mMovePosition = cPosition;
	}

protected:
	bool LoadActor(const gchar* pcFilePath);
	void MoveStopCheck();
	
protected:
	virtual bool InitActionComponents() = 0;
	virtual bool InitInfoCompenent(const gchar* pcID, guint32 uiLevel) = 0;
	virtual void CallbackTimeEvent(Gn2DActor::TimeEvent* pTimeEvent);
	
protected:
	inline void SetInfoComponent(gtuint uiIndex, GInfo* pVal) {
		GnAssert( mInfoComponents.GetAt( uiIndex ) == NULL );
		mInfoComponents.SetAt( uiIndex, pVal );
	}	
	inline void SetActionComponent(gtuint uiIndex, GAction* pVal) {
		GnAssert( mActionComponents.GetAt( uiIndex ) == NULL );
		mActionComponents.SetAt( uiIndex, pVal );
	}
};

#endif
