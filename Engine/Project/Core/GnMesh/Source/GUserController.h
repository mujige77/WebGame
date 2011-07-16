#ifndef __HiroCat__GUserController__
#define __HiroCat__GUserController__

class GUserController : public GActorController
{
private:
	GnMemberSlot1<GUserController, Gn2DActor::TimeEvent*> mCallbackActorEventSlot;

public:
	static GUserController* Create(const gchar* pcID, guint32 uiLevel);

public:
	void Start();
	
protected:
	void ActorCallbackFunc(Gn2DActor::TimeEvent* pEvent);
protected:
	bool InitController();
	bool InitActionComponents();
	bool InitInfoCompenent(const gchar* pcID, guint32 uiLevel);	
	void MoveStopCheck();
};

#endif
