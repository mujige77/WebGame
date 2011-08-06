#include "GamePCH.h"
#include "GSelectStageScene.h"
#include "GSelectStageBGLayer.h"
#include "GSelectStageUILayer.h"
#include "GnIListPageCtrl.h"
#include "GMainGameEnvironment.h"

GSelectStageScene::GSelectStageScene() : mInputEvent( this, &GSelectStageScene::InputEvent )
{
}

GSelectStageScene::~GSelectStageScene()
{
}

GSelectStageScene* GSelectStageScene::CreateScene(guint32 uiLastStage)
{
	GSelectStageScene* scene = new GSelectStageScene();
	if( scene->CreateInterface( uiLastStage ) == false || scene->CreateBackground() == false )
	{
		delete scene;
		return NULL;
	}
	return scene;
}

bool GSelectStageScene::CreateInterface(guint32 uiLastStage)
{
	GSelectStageUILayer* interfaceLayer = new GSelectStageUILayer();
	mpListPageCtrl = (GnIListPageCtrl*)interfaceLayer->CreateInterface(
		GInterfaceLayer::UI_SELECTSTAGE_LIST, &mInputEvent );
	mpListButtonGroup = interfaceLayer->CreateInterface( GInterfaceLayer::UI_SELECTSTAGE_BT, &mInputEvent );
	interfaceLayer->CreateListCtrlItem( uiLastStage );
	if( mpListPageCtrl == NULL || mpListButtonGroup == NULL )
	{
		delete interfaceLayer;
		return false;
	}
	mpInterfaceLayer = interfaceLayer;
	addChild( interfaceLayer, INTERFACE_ZORDER );
	interfaceLayer->release();
	return true;
}

bool GSelectStageScene::CreateBackground()
{
	GSelectStageBGLayer* backLayer = GSelectStageBGLayer::CreateBackground();
	if( backLayer == NULL )
	{
		return false;
	}
	mpBackgroundLayer = backLayer;
	addChild( backLayer );
	backLayer->release();
	return true;
}

void GSelectStageScene::Update(float fTime)
{
	mpInterfaceLayer->Update( fTime );
}

const gchar* GSelectStageScene::GetSceneName()
{
	return SCENENAME_SELECTSTAGE;
}

void GSelectStageScene::InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		if( mpListButtonGroup->GetChild( GInterfaceLayer::BT_NEXT ) == pInterface )
		{
			mpListPageCtrl->SetNextPage();
		}
		else if( mpListButtonGroup->GetChild( GInterfaceLayer::BT_PREVIOUS ) == pInterface )
		{
			mpListPageCtrl->SetPreviousPage();
		}
		else if( mpListButtonGroup->GetChild( GInterfaceLayer::BT_SELECTSTAGE_BACK ) == pInterface )
		{
			GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
		}
		else
		{
			GnIListCtrlItem* listItme = GnDynamicCast( GnIListCtrlItem, pInterface );
			if( listItme )
			{
				gtuint pageItemSize = mpListPageCtrl->GetColumnSize() * mpListPageCtrl->GetRowSize();
				gtuint rowSize = mpListPageCtrl->GetRowSize();
				gtuint numStage = ( mpListPageCtrl->GetCurrentPage() * pageItemSize )
					+ ( ( listItme->GetNumColumn() * rowSize ) + listItme->GetNumRow() );
				
				SelectStage( numStage );
			}
		}
	}
}

void GSelectStageScene::SelectStage(gtuint uiNumStage)
{
//	if( uiNumStage )
//	{
//		CCDirector::sharedDirector()->end();
//		return;
//	}
	GMainGameEnvironment::Create();
	if( GetGameEnvironment()->SetStage( uiNumStage ) == false )
		return;
	
	GScene:SetChangeSceneName( SCENENAME_GAME );
}