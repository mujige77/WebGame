#ifndef GNCOCOSSCENE_H
#define GNCOCOSSCENE_H
#include "GnLayer.h"

class GnCocosScene : public CCScene
{
protected:
	gint32 mID;
	GnLayer* mpState;

public:
	static GnCocosScene* CreateScene(gint32 uiID, GnLayer* pState, bool bAtuoRelease = true);
	virtual ~GnCocosScene();

	inline GnLayer* GetLayer() {
		return mpState;
	}
	inline gint32 GetID() {
		return mID;
	}
	inline void SetID(gint32 val) {
		mID = val;
	}
protected:
	GnCocosScene(GnLayer* pState);	
};

#endif // GNCOCOSSCENE_H