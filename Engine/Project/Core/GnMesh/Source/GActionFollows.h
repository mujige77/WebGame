#ifndef Core_GActionFollows_h
#define Core_GActionFollows_h

class GnIProgressBar;
class GActionFollows : public GAction
{
public:
	enum eFollowType
	{
		eShadow,
	};
private:
	GLayer* mpActorLayer;
	Gn2DMeshObjectPtr mpsFollowMesh;
	GExtraData::eExtraType mFollowExtraType;
	
public:
	GActionFollows(GActorController* pController);
	virtual ~GActionFollows();	
	bool CreateFollow(eFollowType uiFollowsType);
	
public:
	void Update(float fTime);
	void AttachActionToController();
	void DetachActionToController();
	inline gtint GetActionType() {
		return ACTION_FOLLOWS;
	}
public:
	inline void SetActorLayer(GLayer* pActorLayer) {
		mpActorLayer = pActorLayer;
	}
	
protected:
	GnIProgressBar* CreateGageBar();
	void SetFollowPosition();
	
protected:
	inline GLayer* GetActorLayer() {
		return mpActorLayer;
	}
};

#endif
