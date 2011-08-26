#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GScene.h"

const gchar* GScene::SCENENAME_START = "StartScene";
const gchar* GScene::SCENENAME_STATE = "StateScene";;
const gchar* GScene::SCENENAME_SELECTSTAGE = "SelectStageScene";
const gchar* GScene::SCENENAME_GAME = "GameScene";

gstring GScene::mChangeSceneName;
GScene* GScene::smpCurrentScene = NULL;
GDialogPtr GScene::smpsDialog;

void GScene::SetChangeSceneName(const gchar* pcName)
{
	mChangeSceneName = pcName;
}
gstring& GScene::GetChangeSceneName()
{
	return mChangeSceneName;
}

void GScene::SetModalState(GDialog* pDlg)
{
	if( smpCurrentScene == NULL )
		return;

	if( pDlg == NULL )
	{
		if( smpsDialog )
			smpsDialog->Close();
		smpsDialog = NULL;
		GLayer::SetModalState( NULL );
		return;
	}
	GLayer::SetModalState( pDlg->GetDialogInterface() );
	pDlg->Show();
	smpsDialog = pDlg;
}

GDialog* GScene::GetModalStateDialog()
{
	return smpsDialog;
}

void GScene::SetCurrentScene(GScene* pScene)
{
	smpCurrentScene = pScene;
}

GScene* GScene::GetCurrentScene()
{
	return smpCurrentScene;
}

gint GScene::GetMaxZorder()
{
	gint maxZorder = 0;
	CCObject* child;
	CCARRAY_FOREACH(m_pChildren, child)
	{
		CCNode* pNode = (CCNode*) child;
		maxZorder = GnMax( pNode->getZOrder(), maxZorder );
	}
	return maxZorder;
}