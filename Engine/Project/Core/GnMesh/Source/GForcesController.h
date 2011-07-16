#ifndef __HiroCat__GForcesController__
#define __HiroCat__GForcesController__

class GForcesController : public GActorController
{
private:
	GnMemberSlot1<GForcesController, Gn2DActor::TimeEvent*> mCallbackActorEventSlot;

	
public:
	static GForcesController* Create(const gchar* pcID, guint32 uiLevel);
	
protected:
	GForcesController();
	
protected:
	bool InitController();
	bool InitInfoCompenent(const gchar* pcID, guint32 uiLevel);
	bool InitActionComponents();
	void ActorCallbackFunc(Gn2DActor::TimeEvent* pEvent);
	
};

#endif
