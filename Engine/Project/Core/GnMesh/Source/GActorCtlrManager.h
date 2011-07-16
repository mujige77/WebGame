#ifndef __HiroCat__GActorCtlrManager__
#define __HiroCat__GActorCtlrManager__

#include "GActorController.h"

class GActorInfoDatabase;
class GActionAttackCheck;
class GActorCtlrManager : public GnMemoryObject
{
	GnTPrimitiveArray<GActorController*> mActors;
	GnTPrimitiveArray<gtuint> mActorIDs;
	GLayer* mpActorLayer;

protected:
	static const gtuint msNumAttackLine = 2;
	
public:
	GActorCtlrManager(GLayer* pLayer);
	virtual ~GActorCtlrManager();
	//void SetStartPostion(GActorController* pActorController, gtuint uiDirection, gtuint uiAttackLine);

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
	
protected:
	virtual void CollisionCheck(GActionAttackCheck* pAttackCheck, GActorCtlrManager* pCheckCtlrManager);
	virtual gtuint SendAttackToEnemy(GActionAttackCheck* pAttackCheck, GActorCtlrManager* pCheckCtlrManager);
};

#endif
