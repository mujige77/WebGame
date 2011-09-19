#ifndef __Core__GMainGameEnvironment__
#define __Core__GMainGameEnvironment__

#include "GGameEnvironment.h"

class GActorController;
class GMainGameEnvironment : public GGameEnvironment
{
private:
	GnTPrimitiveArray<float> mLines;
	GnFRect mEnableMoveRect;
	
public:
	static GMainGameEnvironment* Create();
	static void Destory();
	static GMainGameEnvironment* GetSingleton();
	
public:
	bool SetStage(gtuint uiNumStage);
	void Reset();
	bool CorrectMoveX(float& fPositionX, bool uiDirection, bool bUser = false);
	bool CorrectMoveY(float& fPositionY);
	void SetStartPositionToActor(GActorController* pActorCtlr, guint32 uiLine, gtuint uiDirection);
	void UserMove(GActorController* pActorCtlr);
public:
	void AddLine(float fLinePos) { // lower to upper
		mLines.Add( fLinePos );
	}
	float GetLine(gtuint uiIndex){
		if( mLines.GetSize() <= uiIndex )
			uiIndex = 0;
		return mLines.GetAt(uiIndex);
	}
	gtuint GetLineCount() {
		return mLines.GetSize();
	}
	void SetEnableMoveRect(GnFRect cRect) {
		mEnableMoveRect = cRect;
	}
	
protected:
	inline GMainGameEnvironment(){};
};

#endif
