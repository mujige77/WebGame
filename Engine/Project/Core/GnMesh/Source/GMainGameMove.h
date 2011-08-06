#ifndef __Core__GMainGameMove__
#define __Core__GMainGameMove__

#include "GActionMove.h"
class GMainGameMove : public GActionMove
{
public:
	GMainGameMove(GActorController* pController);
	
private:
	eMoveType mBeforeVerticalDirection;
	eMoveType mBeforeHorizontalDirection;
	gtuint mNumLine;
	
public:
	inline void SetNumLine(gtuint uiLine) {
		mNumLine = uiLine;
	}
	inline gtuint GetNumLine() {
		return mNumLine;
	}
	
public:
	virtual void SetMove(gtuint uiType);
	
private:
	void SetCurrentLine();
};

#endif
