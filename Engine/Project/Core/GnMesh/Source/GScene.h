#ifndef __HiroCat__GScene__
#define __HiroCat__GScene__
#include <cocos2d.h>
#include "GDialog.h"

class GScene : public cocos2d::CCScene//, public CCTargetedTouchDelegate
{
public:
	static const gchar* SCENENAME_START;
	static const gchar* SCENENAME_STATE;
	static const gchar* SCENENAME_SELECTSTAGE;
	static const gchar* SCENENAME_GAME;
	static const gchar* SCENENAME_OPENING;
	static const gchar* SCENENAME_LOADING;
	
private:
	static gstring mChangeSceneName;
	static GScene* smpCurrentScene;
	static GDialogPtr smpsDialog;
	
public:
	
	static void SetChangeSceneName(const gchar* pcName);
	static gstring& GetChangeSceneName();

	static void SetModalState(GDialog* pDlg);
	static GDialog* GetModalStateDialog();
	static void SetCurrentScene(GScene* pScene);
	static GScene* GetCurrentScene();
public:		
	virtual ~GScene(){}	
	gint GetMaxZorder();
	
public:
	
	
	virtual void Update(float fDeltaTime){};	
	virtual const gchar* GetSceneName() = 0;
	

	
};

#endif
