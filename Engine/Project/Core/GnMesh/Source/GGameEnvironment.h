#ifndef __Core__GGameEnvironment__
#define __Core__GGameEnvironment__

#include "GStageInfo.h"

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
	GStageInfo mStageInfo;
	float mMoveRangeY;
	gtuint mNumUserLine;
	
public:
	static GGameEnvironment* GetSingleton();
	
public:
	virtual bool SetStage(gtuint uiNumStage);
	virtual void Reset(){};
	virtual void UserMove(GActorController* pActorCtlr){};
	virtual void RemoveBasicCurrentAction(GActorController* pActorCtlr);
	virtual void CreateActorControllerBasicAction(GActorController* pActorCtrl);
	virtual void InitActorControllerAction(GLayer* pActorLayer, GActorController* pActorCtrl);
	virtual bool CorrectMoveX(float& fPositionX, bool uiDirection, bool bUser = false) = 0;
	virtual bool CorrectMoveY(float& fPositionY) = 0;
	virtual void SetStartPositionToActor(GActorController* pActorCtlr, guint32 uiLine, gtuint uiDirection) = 0;
	template<class T>
	void CreateActionToActorController(GActorController* pActorCtrl);	
	
public:
	inline GStageInfo* GetStageInfo() {
		return &mStageInfo;
	}
	inline float GetMoveRangeY() {
		return mMoveRangeY;
	}
	inline void SetMoveRangeY(float val) {
		mMoveRangeY =  val;
	}
	inline void SetNumUserLine(gtuint uiLine) {
		mNumUserLine = uiLine;
	};
	inline gtuint GetNumUserLine() {
		return mNumUserLine;
	}
};

#define GetGameEnvironment GGameEnvironment::GetSingleton
#endif
