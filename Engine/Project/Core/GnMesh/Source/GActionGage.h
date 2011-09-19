#ifndef __Core__GActionGage__
#define __Core__GActionGage__

//#include "GAction.h"

class GnIProgressBar;
class GActionGage : public GAction
{
private:
	GLayer* mpActorLayer;
	GnIProgressBar* mpGageBar;
	float mViewGageTime;
	float mAcumTime;
	gint32 mGagePercent;

public:
	GActionGage(GActorController* pController);
	virtual ~GActionGage();

	void SetGagePercent(gint32 iPercent);

// virtual
public:
	void Update(float fTime);
	void AttachActionToController();
	void DetachActionToController();
	inline gtint GetActionType() {
		return ACTION_GAGE;
	}
	inline bool IsStopAction() {
		return mViewGageTime <= mAcumTime;
	}

// inline
public:
	inline void SetActorLayer(GLayer* pActorLayer) {
		mpActorLayer = pActorLayer;
	}
	
protected:
	GnIProgressBar* CreateGageBar();
	void SetGagePosition();
	
protected:
	inline GLayer* GetActorLayer() {
		return mpActorLayer;
	}
};

#endif
