#ifndef __Core__GMainGameInterfaceLayer__
#define __Core__GMainGameInterfaceLayer__

#include "GInterfaceLayer.h"

class GnIButton;
class GnIInterfaceGroup;
class GEnergyBar;
class GMainGameInterfaceLayer : public GInterfaceLayer
{
public:
	class ButtonInfo
	{
	private:
		gint32 mCanPushEnergy;
		float mCoolTime;
		GnIButton* mpButton;
		
	public:
		inline gint32 GetCanPushEnergy() {
			return mCanPushEnergy;
		}
		inline void SetCanPushEnergy(gint32 val) {
			mCanPushEnergy = val;
		}
		inline float GetCoolTime() {
			return mCoolTime;
		}
		inline void SetCoolTime(float val) {
			mCoolTime = val;
		}
		inline void SetButton(GnIButton* pButton) {
			mpButton = pButton;
		};
		inline GnIButton* GetButton() {
			return mpButton;
		}
	};
	
private:
	GnTPrimitiveArray<ButtonInfo> mForcesButtonInfos;
	GnInterfaceGroup* mpForcesButtonGroup;
	GEnergyBar* mpForcesEnergyBar;
	GnMemberSlot2<GMainGameInterfaceLayer, GnInterface*, GnIInputEvent*> mForcesInputEvent;
	
public:
	inline static GInterfaceLayer* Create(const gchar* pcName) {
		CCSprite* sprite = CCSprite::spriteWithFile( pcName );		
		if( sprite == NULL )
			return NULL;
		GInterfaceLayer* layer = new GMainGameInterfaceLayer();
		layer->Create( sprite );
		return layer;
	}
	
public:
	GMainGameInterfaceLayer();
	GnInterfaceGroup* CreateInterface(gtuint uiIndex
		, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot);
	
public:
	virtual void Update(float fTime);
	
protected:
	GnInterfaceGroup* CreateMainController();
	GnInterfaceGroup* CreateMainForcesButtons();
	GnInterfaceGroup* CreateMainSkillButtons();
	bool SetForcesButtonInfo(GnIButton** ppButtons);
	void UpdateButtonState();
	void InputForcesButton(GnInterface* pInterface, GnIInputEvent* pEvent);
};

#endif
