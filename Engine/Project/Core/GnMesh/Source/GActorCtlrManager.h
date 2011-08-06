#ifndef __HiroCat__GActorCtlrManager__
#define __HiroCat__GActorCtlrManager__

#include "GActorController.h"

class GActorInfoDatabase;
class GActionAttackCheck;
class GCastle;
class GActorCtlrManager : public GnSmartObject
{
	GnTPrimitiveArray<GActorController*> mActors;
	GnTPrimitiveArray<gtuint> mActorIDs;
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
	inline GActorController* GetActorCtlr(gtuint uiIndex)	{
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
};

GnSmartPointer(GActorCtlrManager);
#endif
