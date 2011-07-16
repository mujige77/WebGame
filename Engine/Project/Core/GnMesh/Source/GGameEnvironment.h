#ifndef __Core__GGameEnvironment__
#define __Core__GGameEnvironment__

class GLayer;
class GAction;
class GActionMove;
class GActionDamage;
class GActorController;

#define INTERFACE_ZORDER 100
class GGameEnvironment : public GnMemoryObject
{
protected:
	static GGameEnvironment* mpSingleton;
	
public:
	static GGameEnvironment* GetSingleton();
	
public:
	virtual void Reset(){};
	virtual void UserMove(GAction* pMoveAction){};
	virtual void RemoveBasicCurrentAction(GActorController* pActorCtlr);
	virtual void CreateActorControllerBasicAction(GActorController* pActorCtrl);
	virtual void InitActorControllerAction(GLayer* pActorLayer, GActorController* pActorCtrl);
	virtual bool CorrectMove(GnVector2& position) = 0;
	virtual void SetStartPositionToActor(GActorController* pActorCtlr, gtuint uiDirection) = 0;
	template<class T>
	void CreateActionToActorController(GActorController* pActorCtrl);	
};

#define GetGameEnvironment GGameEnvironment::GetSingleton
#endif
