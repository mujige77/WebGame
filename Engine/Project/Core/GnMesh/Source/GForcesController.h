#ifndef __HiroCat__GForcesController__
#define __HiroCat__GForcesController__

class GForcesController : public GActorController
{
public:
	static GForcesController* Create(const gchar* pcID, guint32 uiLevel);
	
protected:
	GForcesController();
	
protected:
	bool InitInfoCompenent(const gchar* pcID, guint32 uiLevel);
	bool InitActionComponents();
	
};

#endif
