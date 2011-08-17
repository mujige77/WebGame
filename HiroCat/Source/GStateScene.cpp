#include "GamePCH.h"
#include "GStateScene.h"
#include "GStateBGLayer.h"
#include "GStateUILayer.h"
#include "GAbilityListCtrlItem.h"
#include "GItemListCtrlItem.h"
#include "GStateListCtrlItem.h"
#include "GnIListCtrl.h"
#include "GPlayingDataManager.h"
#include "GItemInfo.h"
#include "GUnitViewer.h"
#include "GnITabCtrl.h"

GStateScene::GStateScene() : mOtherInputEvent( this, &GStateScene::OtherInputEvent )
	, mUnitInputEvent( this, &GStateScene::UnitInputEvent ), mShopInputEvent( this, &GStateScene::ShopInputEvent )
	, mAbilityInputEvent( this, &GStateScene::AbilityInputEvent ), mpCurrentStetItem( NULL )
	, mpCurrentShopItem( NULL ), mpCurrentInvenItem( NULL), mpCurrentEquipItem( NULL ), mCurrentControllerIndex( -1 )
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
	mpOtherUIGroup = interfaceLayer->CreateInterface( GInterfaceLayer::UI_STATE_OTHERUI, &mOtherInputEvent );	
	if( mpOtherUIGroup == NULL 
	   || interfaceLayer->CreateInterface( GInterfaceLayer::UI_STATE_UNITTAB, &mUnitInputEvent ) == NULL	    
	   || interfaceLayer->CreateInterface( GInterfaceLayer::UI_STATE_ABILITYTAB, &mAbilityInputEvent ) == NULL
	   || interfaceLayer->CreateInterface( GInterfaceLayer::UI_STATE_SHOPTAB, &mShopInputEvent ) == NULL )
	{
		delete interfaceLayer;
		return false;
	}
	
	
	mpInterfaceLayer = interfaceLayer;
	addChild( interfaceLayer, INTERFACE_ZORDER );
	interfaceLayer->release();
	
	GnList<GUserHaveItem::Item> haveUnits;
	
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();	
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();	
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );	
	
	haveItem->GetItems( eUnit, haveUnits );	
	
	haveItem->Close();
	
	
	mpsUnitViewer = GUnitViewer::CreateUnitViewer( haveUnits );
	
	GnITabPage* tabPage = interfaceLayer->GetTabCtrl()->GetTabPage( GStateUILayer::UNIT_TAB );
	tabPage->AddChild( mpsUnitViewer, INTERFACE_ZORDER + 10 );
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
	//mpsUnitViewer->Update( fTime );
}

const gchar* GStateScene::GetSceneName()
{
	return SCENENAME_STATE;
}

void GStateScene::OtherInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		if( mpOtherUIGroup->GetChild( GInterfaceLayer::BT_STATE_FRONT ) == pInterface )
		{
			GScene::SetChangeSceneName( GScene::SCENENAME_SELECTSTAGE );
		}
		else if( mpOtherUIGroup->GetChild( GInterfaceLayer::BT_STATE_BACK ) == pInterface )
		{
			GScene::SetChangeSceneName( GScene::SCENENAME_START );
		}
	}
}

void GStateScene::UnitInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSH )
	{
		if( pInterface->GetTegID() > -1 )
			ViewUnit( (guint32)pInterface->GetTegID() );
	}
	else if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		switch( pInterface->GetTegID() )
		{
			case GInterfaceLayer::BT_UNIT_UPGRADE:
				//UpgradeAbility( mpCurrentStetItem )
				break;
		}
	}
}

void GStateScene::ShopInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSH )
	{
		if( pInterface->GetTegID() == GInterfaceLayer::LISTITEM_SHOP )
		{
			if( ViewItemExplain( mpCurrentShopItem, pInterface ) )
			{
				if( mpCurrentInvenItem )
					mpCurrentInvenItem->SetVisibleExplain( false );
				if( mpCurrentEquipItem )
					mpCurrentEquipItem->SetVisibleExplain( false );
			}
		}
		else if( pInterface->GetTegID() == GInterfaceLayer::LISTITEM_INVEN )
		{
			if( ViewItemExplain( mpCurrentInvenItem, pInterface ) )
			{
				if( mpCurrentShopItem )
					mpCurrentShopItem->SetVisibleExplain( false );
				if( mpCurrentEquipItem )
					mpCurrentEquipItem->SetVisibleExplain( false );
			}
		}
		else
		{
			if( ViewItemExplain( mpCurrentEquipItem, pInterface ) )
			{
				if( mpCurrentShopItem )
					mpCurrentShopItem->SetVisibleExplain( false );
				if( mpCurrentInvenItem )
					mpCurrentInvenItem->SetVisibleExplain( false );	
			}
		}
	}
	else if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;
		switch( pInterface->GetTegID() )
		{
			case GInterfaceLayer::BT_BUY_ITEM:
				BuyItem( interfaceLayer->GetInventoryListCtrl(), interfaceLayer->GetMoneyLabel()
					, mpCurrentShopItem );
				break;
			case GInterfaceLayer::BT_SELL_ITEM:
				SellItem( interfaceLayer->GetInventoryListCtrl(), interfaceLayer->GetMoneyLabel()
					, mpCurrentInvenItem );
				mpCurrentInvenItem = NULL;
				break;
			case GInterfaceLayer::BT_EQUIP_ITEM:
				EquipItem( interfaceLayer->GetInventoryListCtrl(), interfaceLayer->GetEquipListCtrl()
					, mpCurrentInvenItem );
				mpCurrentInvenItem = NULL;
				break;
			case GInterfaceLayer::BT_UNEQUIP_ITEM:
				UnEquipItem( interfaceLayer->GetInventoryListCtrl(), interfaceLayer->GetEquipListCtrl()
					, mpCurrentEquipItem );
				mpCurrentEquipItem = NULL;
				break;
		}	
	}
}
void GStateScene::AbilityInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSH )
	{
		ViewItemExplain( mpCurrentStetItem, pInterface );
	}
	else if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;
		switch( pInterface->GetTegID() )
		{
			case GInterfaceLayer::BT_ABILITY_UPGRADE:
				UpgradeAbility( interfaceLayer->GetStarLabel(), mpCurrentStetItem );
				break;
		}
	}
}

bool GStateScene::ViewItemExplain(GStateListCtrlItem*& pCurrentItem, GnInterface* pInterface)
{
	GStateListCtrlItem* stetItem = GnDynamicCast( GStateListCtrlItem, pInterface );		
	if( stetItem )
	{
		if( pCurrentItem )
			pCurrentItem->SetVisibleExplain( false );
		pCurrentItem = stetItem;
		stetItem->SetVisibleExplain( true );
		return true;
	}
	return false;
}

void GStateScene::SellItem(GnIListCtrl* pListCtrl, GnINumberLabel* pMoneyLabel, GStateListCtrlItem* pItem)
{
	if( pItem == NULL )
		return;
	
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );
	
	guint32 sellMoney = GetItemInfo()->GetSellPrice( pItem->GetItemIndex() - INDEX_ITEM );
	
	// delete item
	haveItem->DeleteItem( pItem->GetItemIndex(), eItem );
	pListCtrl->RemoveItem( pItem );
	
	// set money
	guint32 money = sellMoney + playingData->GetMoneyCount();
	playingData->SetMoneyCount( money );
	pMoneyLabel->SetNumber( money );
	
	haveItem->Close();
	
	dataMng->SaveData();
}

void GStateScene::BuyItem(GnIListCtrl* pListCtrl, GnINumberLabel* pMoneyLabel, GStateListCtrlItem* pItem)
{
	if( pItem == NULL )
		return;	
	
	gtuint iteminfoIndex = pItem->GetItemIndex() - INDEX_ITEM;
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();

	GPlayingData* playingData = dataMng->GetPlayingPlayerData();	
	guint32 buyMoney = GetItemInfo()->GetBuyPrice( iteminfoIndex );
	if( playingData->GetMoneyCount() < buyMoney )
		return;

	// add item to haveitem
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );	
	haveItem->AddItem( pItem->GetItemIndex(), eItem );
	haveItem->Close();
	
	GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;
	GItemListCtrlItem* newItem = interfaceLayer->CreateItemCtrlItem( iteminfoIndex );
	newItem->SetTegID( GInterfaceLayer::LISTITEM_INVEN );
	pListCtrl->AddItem( newItem );
	
	// set money
	guint32 money = playingData->GetMoneyCount() - buyMoney;
	playingData->SetMoneyCount( money );
	pMoneyLabel->SetNumber( money );	
	
	dataMng->SaveData();
}
 
void GStateScene::EquipItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GStateListCtrlItem* pItem)
{
	if( pItem == NULL )
		return;
	if( pEquipList->GetItemCount() >= ENABLE_MAX_EQUIP )
		return;
	
	gtuint iteminfoIndex = pItem->GetItemIndex() - INDEX_ITEM;
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	
	// add equip item to haveitem
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );	
	haveItem->DeleteItem( pItem->GetItemIndex(), eItem );
	haveItem->AddItem( pItem->GetItemIndex(), eEquip );
	haveItem->Close();
	
	// add equip
	GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;
	GItemListCtrlItem* newItem = interfaceLayer->CreateEquipCtrlItem( iteminfoIndex );
	newItem->SetTegID( GInterfaceLayer::LISTITEM_EQUIP );
	pEquipList->AddItem( newItem );	
	
	// remove invenitem
	pInvenList->RemoveItem( pItem );	
}
void GStateScene::UnEquipItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GStateListCtrlItem* pItem)
{
	if( pItem == NULL )
		return;
	
	gtuint iteminfoIndex = pItem->GetItemIndex() - INDEX_ITEM;
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	
	// add equip item to haveitem
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );	
	haveItem->DeleteItem( pItem->GetItemIndex(), eEquip );
	haveItem->AddItem( pItem->GetItemIndex(), eItem );
	haveItem->Close();
	
	// add equip
	GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;
	GItemListCtrlItem* newItem = interfaceLayer->CreateItemCtrlItem( iteminfoIndex );
	newItem->SetTegID( GInterfaceLayer::LISTITEM_INVEN );
	pInvenList->AddItem( newItem );	
	
	// remove invenitem
	pEquipList->RemoveItem( pItem );
}

void GStateScene::UpgradeAbility(GnINumberLabel* pStartLabel, GStateListCtrlItem*& pCurrentItem)
{
	GAbilityListCtrlItem* ablityItem = GnDynamicCast(GAbilityListCtrlItem, pCurrentItem);
	if( ablityItem == NULL )
		return;
	
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	
	if( playingData->GetStarCount() < 1 )
		return;
	
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );	
	guint32 level = haveItem->GetItemLevel( ablityItem->GetItemIndex() );
	if( MAX_ABILITY_LEVEL <= level )
	{
		haveItem->Close();
		return;
	}

	// update label level 
	ablityItem->SetCurrentLevel( ablityItem->GetCurrentLevel() + 1 );
	
	// update have item level
	haveItem->UpdateLevel( ablityItem->GetItemIndex(), ablityItem->GetCurrentLevel() );
	haveItem->Close();
	
	// set money
	guint32 star = playingData->GetStarCount() - 1;
	playingData->SetStarCount( star );
	pStartLabel->SetNumber( star );	
	
	dataMng->SaveData();
}

void GStateScene::ViewUnit(guint32 uiUnitIndex)
{
	
	GActorController* ctrl = mpsUnitViewer->GetActorCtrlFromUnitIndex( uiUnitIndex );
	if( ctrl )
	{
		if( mCurrentControllerIndex != -1 )
			mpsUnitViewer->SetVisibleActorCtlr( (guint32)mCurrentControllerIndex, false );
		mpsUnitViewer->SetVisibleActorCtlr( uiUnitIndex, true );
		mCurrentControllerIndex = uiUnitIndex;
		
	}
}