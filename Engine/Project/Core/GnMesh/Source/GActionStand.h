
#ifndef __Core__GActionStand__
#define __Core__GActionStand__

class GActionStand : public GAction
{
public:
	inline GActionStand(GActorController* pController) : GAction( pController )
	{}

public:
	inline gtint GetActionType() {
		return ACTION_STAND;
	}
	inline void AttachCompentToController() {
		GetController()->AddCurrentAction( this );
		GetController()->GetActor()->SetTargetAnimation( ANI_STAND );
	};
};
#endif
