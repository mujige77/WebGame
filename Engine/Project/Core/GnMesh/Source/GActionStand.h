
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
	inline void AttachActionToController() {
		GetController()->SetMoveDeltaPosition( GnVector2( 0.0f, 0.0f ) );
		GetController()->GetActor()->SetTargetAnimation( ANI_STAND );
	};
};
#endif
