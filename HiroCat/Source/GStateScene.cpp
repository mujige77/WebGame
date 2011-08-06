#include "GamePCH.h"
#include "GStateScene.h"
#include "GStateBGLayer.h"
#include "GStateUILayer.h"

GStateScene::GStateScene() : mInputEvent( this, &GStateScene::InputEvent )
{
}

GStateScene::~GStateScene()
{
}

GStateScene* GStateScene::CreateScene()
{
	GStateScene* scene = new GStateScene();
	if( scene->CreateInterface() == false || scene->CreateBackground() == false )
	{
		delete scene;
		return NULL;
	}
	return scene;
}

bool GStateScene::CreateInterface()
{
	GStateUILayer* interfaceLayer = new GStateUILayer();
	mpOtherUIGroup = interfaceLayer->CreateInterface( GInterfaceLayer::UI_STATE_OTHERUI, &mInputEvent );
	if( mpOtherUIGroup == NULL )
	{
		delete interfaceLayer;
		return false;
	}
	mpInterfaceLayer = interfaceLayer;
	addChild( interfaceLayer, INTERFACE_ZORDER );
	interfaceLayer->release();
	return true;
}

bool GStateScene::CreateBackground()
{
	GStateBGLayer* backLayer = GStateBGLayer::CreateBackground();
	if( backLayer == NULL )
	{
		return false;
	}
	mpBackgroundLayer = backLayer;
	addChild( backLayer );
	backLayer->release();
	return true;
}

void GStateScene::Update(float fTime)
{
	mpInterfaceLayer->Update( fTime );
}

const gchar* GStateScene::GetSceneName()
{
	return SCENENAME_STATE;
}

void GStateScene::InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		if( mpOtherUIGroup->GetChild( GInterfaceLayer::BT_STATE_FRONT ) == pInterface )
		{
			GScene::SetChangeSceneName( GScene::SCENENAME_SELECTSTAGE );
		}
	}
	
}