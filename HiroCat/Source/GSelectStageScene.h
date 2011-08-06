#ifndef HiroCat_GSelectStageScene_h
#define HiroCat_GSelectStageScene_h

class GnIListPageCtrl;
class GnInterfaceGroup;
class GSelectStageScene : public GScene
{
private:
	GLayer* mpInterfaceLayer;
	GLayer* mpBackgroundLayer;
	GnIListPageCtrl* mpListPageCtrl;
	GnInterfaceGroup* mpListButtonGroup;
	GnMemberSlot2<GSelectStageScene, GnInterface*, GnIInputEvent*> mInputEvent;
	
public:
	GSelectStageScene();
	virtual ~GSelectStageScene();
	
public:
	static GSelectStageScene* CreateScene(guint32 uiLastStage);
	bool CreateInterface(guint32 uiLastStage);
	bool CreateBackground();
public:
	virtual void Update(float fTime);
	virtual const gchar* GetSceneName();
	
protected:
	void InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
	void SelectStage(gtuint uiNumStage);
};

#endif
