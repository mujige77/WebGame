#ifndef __Core__GGameEnvironment__
#define __Core__GGameEnvironment__

class GAction;
class GActionMove;
class GActorController;
class GGameEnvironment : public GnMemoryObject
{
protected:
	static GGameEnvironment* mpSingleton;
	
public:
	static GGameEnvironment* GetSingleton();
	
public:
	virtual void Reset(){};
	virtual void UserMove(GAction* pMoveAction){};
	virtual bool CorrectMove(GnVector2& position) = 0;
	virtual void SetStartPositionToActor(GActorController* pActorCtlr, gtuint uiDirection) = 0;
	
};

#define GetGameEnvironment GGameEnvironment::GetSingleton
#endif
