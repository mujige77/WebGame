#ifndef __HiroCat__GMobController__
#define __HiroCat__GMobController__

class GEnemyController : public GActorController
{
private:
	GnMemberSlot1<GEnemyController, Gn2DActor::TimeEvent*> mCallbackActorEventSlot;
	
public:
	static GEnemyController* Create(const gchar* pcID, guint32 uiLevel);
	
protected:
	GEnemyController();

protected:
	bool InitController();
	bool InitActionComponents();
	bool InitInfoCompenent(const gchar* pcID, guint32 uiLevel);
	void ActorCallbackFunc(Gn2DActor::TimeEvent* pEvent);
};

#endif
