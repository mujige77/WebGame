#ifndef HiroCat_GStateScene_h
#define HiroCat_GStateScene_h

class GnIListPageCtrl;
class GnInterfaceGroup;
class GStateScene : public GScene
{
private:
	GLayer* mpInterfaceLayer;
	GLayer* mpBackgroundLayer;
	GnInterfaceGroup* mpOtherUIGroup;
	GnMemberSlot2<GStateScene, GnInterface*, GnIInputEvent*> mInputEvent;
	
public:
	GStateScene();
	virtual ~GStateScene();
	
public:
	static GStateScene* CreateScene();
	bool CreateInterface();
	bool CreateBackground();
	
public:
	virtual void Update(float fTime);
	virtual const gchar* GetSceneName();
	
protected:
	void InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
};


#endif
