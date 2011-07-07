#ifndef __Core__GMainGameEnvironment__
#define __Core__GMainGameEnvironment__

#include "GGameEnvironment.h"

class GActorController;
class GMainGameEnvironment : public GGameEnvironment
{
private:
	GnTPrimitiveArray<float> mLines;
	GnFRect mEnableMoveRect;
	float mMoveRangeY;
	gtuint mNumUserLine;
	
public:
	static GMainGameEnvironment* Create();
	static void Destory();
	static GMainGameEnvironment* GetSingleton();
	
public:
	void Reset();
	bool CorrectMove(GnVector2& cPosition);
	void SetStartPositionToActor(GActorController* pActorCtlr, gtuint uiDirection);
	void UserMove(GAction* pMoveAction);
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
	inline void SetMoveRangeY(float val) {
		mMoveRangeY =  val;
	}
	inline void SetNumUserLine(gtuint uiLine) {
		mNumUserLine = uiLine;
	};
	inline gtuint GetNumUserLine() {
		return mNumUserLine;
	}
	

	
protected:
	inline GMainGameEnvironment(){};
};

#endif
