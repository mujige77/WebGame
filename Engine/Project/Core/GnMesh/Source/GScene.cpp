#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GScene.h"

const gchar* GScene::SCENENAME_START = "StartScene";
const gchar* GScene::SCENENAME_STATE = "StateScene";;
const gchar* GScene::SCENENAME_SELECTSTAGE = "SelectStageScene";
const gchar* GScene::SCENENAME_GAME = "GameScene";

gstring GScene::mChangeSceneName;

void GScene::SetChangeSceneName(const gchar* pcName)
{
	mChangeSceneName = pcName;
}
gstring& GScene::GetChangeSceneName()
{
	return mChangeSceneName;
}