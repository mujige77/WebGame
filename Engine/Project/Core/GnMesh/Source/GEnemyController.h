#ifndef __HiroCat__GMobController__
#define __HiroCat__GMobController__

class GEnemyController : public GActorController
{
public:
	static GEnemyController* Create(const gchar* pcID, guint32 uiLevel);
	
protected:
	GEnemyController();

protected:
	bool InitActionComponents();
	bool InitInfoCompenent(const gchar* pcID, guint32 uiLevel);
};

#endif
