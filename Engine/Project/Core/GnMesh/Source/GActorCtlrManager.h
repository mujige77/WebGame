#ifndef __HiroCat__GActorCtlrManager__
#define __HiroCat__GActorCtlrManager__

#include "GActorController.h"
#include "GFarAttack.h"

class GActorInfoDatabase;
class GActionAttackCheck;
class GCastle;

class GActorCtlrManager : public GnSmartObject
{
	GnTPrimitiveArray<GActorController*> mActors;
	GnTPrimitiveArray<gtuint> mActorIDs;
	GnTObjectArray<GFarAttackPtr> mFarAttacks;
	GLayer* mpActorLayer;
	GCastle* mpCastle;
	
protected:
	static const gtuint msNumAttackLine = 2;
	
public:
	GActorCtlrManager(GLayer* pLayer, GCastle* pCastle = NULL);
	virtual ~GActorCtlrManager();
	
public:
	virtual void Update(float fDeltaTime);
	virtual void ProcessAttack(GActorCtlrManager* pCheckCtlrManager);
	
public:
	inline void AddActorCtlr(GActorController* pActorCtlr) {
		GetActorLayer()->AddChild( pActorCtlr->GetMesh()
			, (int)(GetGameState()->GetGameHeight() - pActorCtlr->GetPosition().y) );
		mActors.Add( pActorCtlr );
	};
	GNFORCEINLINE void RemoveAndDeleteActorCtlr(gtuint uiIndex) {
		GActorController* actorCtlr = mActors.GetAt( uiIndex );
		mActors.RemoveAtAndFill( uiIndex );
		GetActorLayer()->RemoveChild( actorCtlr->GetMesh() );
#ifdef GNDEBUG
		if( actorCtlr->GetDebugLayer() )
			GetActorLayer()->removeChild( actorCtlr->GetDebugLayer(), true );
#endif
		GnDelete actorCtlr;
	}
	inline void AddFarAttack(GFarAttack* pAttack, gint iZorder = 1) {
		GetActorLayer()->AddChild( pAttack->GetAttackMesh(), iZorder );
		
#ifdef GNDEBUG
		if( pAttack->GetDebugLayer() )
			GetActorLayer()->addChild( pAttack->GetDebugLayer() );
#endif
		
		mFarAttacks.Add( pAttack );
	}
	inline void RemoveFarAttack(gtuint uiIndex) {
		GFarAttack* attack = mFarAttacks.GetAt( uiIndex );		
		GetActorLayer()->RemoveChild( attack->GetAttackMesh() );
		
#ifdef GNDEBUG
		if( attack->GetDebugLayer() )
			GetActorLayer()->removeChild( attack->GetDebugLayer(), true );
#endif
		
		mFarAttacks.RemoveAtAndFill( uiIndex );
	}
	inline GFarAttack* GetFarAttack(gtuint uiIndex) {
		return mFarAttacks.GetAt( uiIndex );
	}
	inline gtuint GetFarAttackSize() {
		return mFarAttacks.GetSize();
	}
	inline GActorController* GetActorCtlr(gtuint uiIndex) {
		return mActors.GetAt( uiIndex );
	}
	inline gtuint GetActorCtlrSize() {
		return mActors.GetSize();
	}
	inline void AddEnableActorIndex(gtuint uiIndex) {
		mActorIDs.Add( uiIndex );
	};
	inline gtuint GetActorIndex(gtuint uiIndex) {
		return mActorIDs.GetAt( uiIndex );
	}
	inline gtuint GetActorIndexSize() {
		return mActorIDs.GetSize();
	}
	inline GLayer* GetActorLayer() {
		return mpActorLayer;
	}
	inline GCastle* GetCastle() {
		return mpCastle;
	}
protected:
	virtual void CollisionCheck(GActionAttackCheck* pAttackCheck, GActorCtlrManager* pCheckCtlrManager);
	virtual gtuint SendAttackToEnemy(GActionAttackCheck* pAttackCheck, GActorCtlrManager* pCheckCtlrManager);
	bool CollisionCheck(GActionAttackCheck* pAttackCheck, GActorController* pCheckCtrl);
	bool CastleCollisionCheck(GActionAttackCheck* pAttackCheck, GCastle* pCheckCastel);
	bool FarAttackCollisionCheck(GFarAttack* pFarAttack, GActorController* pCheckCtrl);
	GActionAttackCheck* EnableAttackToCtrl(GActorController* pCtrl);	
};

GnSmartPointer(GActorCtlrManager);
#endif
