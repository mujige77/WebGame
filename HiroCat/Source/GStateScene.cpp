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
		{
			GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;			
			SelectUnit( (guint32)pInterface->GetTegID(), interfaceLayer->GetUnitMoneyLabel() );
		}
	}
	else if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;
		switch( pInterface->GetTegID() )
		{
			case GInterfaceLayer::BT_UNIT_UPGRADE:
				UpgradeUnit( mCurrentControllerIndex, interfaceLayer->GetMoneyLabel()
					, interfaceLayer->GetUnitMoneyLabel() );
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
				BuyItem( interfaceLayer->GetInventoryListCtrl(), interfaceLayer->GetEquipListCtrl()
					, interfaceLayer->GetMoneyLabel(), mpCurrentShopItem );
				break;
			case GInterfaceLayer::BT_SELL_ITEM:
				if( SellItem( interfaceLayer->GetInventoryListCtrl(), interfaceLayer->GetEquipListCtrl()
					, interfaceLayer->GetMoneyLabel(), mpCurrentInvenItem ) == 0 )
				{
					if( mpCurrentInvenItem )
					{
						mpCurrentInvenItem->SetVisibleExplain( false );
						mpCurrentInvenItem = NULL;
					}
				}
				break;
			case GInterfaceLayer::BT_EQUIP_ITEM:
				EquipItem( interfaceLayer->GetInventoryListCtrl(), interfaceLayer->GetEquipListCtrl()
					, mpCurrentInvenItem );
//				if( mpCurrentInvenItem )
//				{
//					mpCurrentInvenItem->SetVisibleExplain( false );
//					mpCurrentInvenItem = NULL;
//				}
				break;
			case GInterfaceLayer::BT_UNEQUIP_ITEM:
				UnEquipItem( interfaceLayer->GetInventoryListCtrl(), interfaceLayer->GetEquipListCtrl()
					, mpCurrentEquipItem );
				if( mpCurrentEquipItem )
				{
					mpCurrentEquipItem->SetVisibleExplain( false );
					mpCurrentEquipItem = NULL;
				}
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

guint32 GStateScene::SellItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GnINumberLabel* pMoneyLabel
	, GStateListCtrlItem* pItem)
{
	if( pItem == NULL )
		return 0;
	
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );
	
	guint32 itemIndex = pItem->GetItemIndex();
	// delete item
	guint32 itemCount = haveItem->GetItemCount( itemIndex ) - 1;
	if( itemCount < 1 )
	{
		GItemListCtrlItem* existItem = GetListCtrlItemFromIndex( pInvenList, itemIndex );
		if( existItem )
		{
			haveItem->DeleteItem( itemIndex, eItem );
			pInvenList->RemoveItem( pItem );
		}
		
		existItem = GetListCtrlItemFromIndex( pEquipList, itemIndex );
		if( existItem )
		{
			haveItem->DeleteItem( itemIndex, eEquip );
			pEquipList->RemoveItem( pItem );
		}		
	}
	else
	{
		UpdateItemCount( haveItem, pInvenList, pEquipList, itemIndex, itemCount );
	}

	// set money
	guint32 sellMoney = GetItemInfo()->GetSellPrice( itemIndex, 0 );
	guint32 money = sellMoney + playingData->GetMoneyCount();
	playingData->SetMoneyCount( money );
	pMoneyLabel->SetNumber( money );
	
	haveItem->Close();
	
	dataMng->SaveData();
	return itemCount;
}

void GStateScene::BuyItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GnINumberLabel* pMoneyLabel
	, GStateListCtrlItem* pItem)
{
	if( pItem == NULL )
		return;	
	
	gtuint itemIndex = pItem->GetItemIndex();
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();	
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	
	guint32 buyMoney = GetItemInfo()->GetBuyPrice( itemIndex, 0 );
	if( playingData->GetMoneyCount() < buyMoney )
		return;

	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );

	GItemListCtrlItem* equipItem = NULL;
	guint32 itemCount = haveItem->GetItemCount( pItem->GetItemIndex() ) + 1;
	
	if( itemCount == 1 )
	{
		// add item to haveitem
		haveItem->AddItem( itemIndex, eItem );
		
		// add item to list
		GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;
		equipItem = interfaceLayer->CreateItemCtrlItem( itemIndex );
		pInvenList->AddItem( equipItem );
		equipItem->SetTegID( GInterfaceLayer::LISTITEM_INVEN );
		equipItem->SetItemIndex( itemIndex );
		equipItem->SetItemCount( itemCount );
	}
	else
	{
		UpdateItemCount( haveItem, pInvenList, pEquipList, itemIndex, itemCount );
	}
	
	haveItem->Close();
	
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
	
	gtuint itemIndex = pItem->GetItemIndex();
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	
	if( GetListCtrlItemFromIndex(pEquipList, pItem->GetItemIndex() ) == NULL )
	{
		GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
		haveItem->OpenPlayerItem( playingData->GetPlayerName() );
		guint32 itemCount = haveItem->GetItemCount( itemIndex );
		
		// add equip item to haveitem
		haveItem->AddItem( itemIndex, eEquip, 0, itemCount );
		
		// add equip
		GStateUILayer* interfaceLayer = (GStateUILayer*)mpInterfaceLayer;
		GItemListCtrlItem* newItem = interfaceLayer->CreateEquipCtrlItem( itemIndex );
		newItem->SetTegID( GInterfaceLayer::LISTITEM_EQUIP );
		
		newItem->SetItemIndex( itemIndex );
		newItem->SetItemCount( itemCount );
		pEquipList->AddItem( newItem );
		
		haveItem->Close();
	}
}
void GStateScene::UnEquipItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GStateListCtrlItem* pItem)
{
	if( pItem == NULL )
		return;
	
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	
	// delete equip item to haveitem
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );
	haveItem->DeleteItem( pItem->GetItemIndex(), eEquip );	
	haveItem->Close();
	
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

void GStateScene::SelectUnit(guint32 uiUnitIndex, GnINumberLabel* pUnitMoneyLabel)
{
	// view unit
	GActorController* ctrl = mpsUnitViewer->GetActorCtrlFromUnitIndex( uiUnitIndex );
	if( ctrl )
	{
		if( mCurrentControllerIndex != -1 )
			mpsUnitViewer->SetVisibleActorCtlr( (guint32)mCurrentControllerIndex, false );
		mpsUnitViewer->SetVisibleActorCtlr( uiUnitIndex, true );
		mCurrentControllerIndex = uiUnitIndex;	
	}
	
	if( eIndexC1 <= uiUnitIndex && eMaxIndexUnit > uiUnitIndex )
	{
		GUserHaveItem* haveItem = GetCurrentHaveItem();
		
		// set upgrade money
		guint32 itemLevel = haveItem->GetItemLevel( uiUnitIndex );	
		guint32 price = GetItemInfo()->GetBuyPrice( uiUnitIndex, itemLevel );
		pUnitMoneyLabel->SetNumber( price );
		
		haveItem->Close();	
	}	
}

void GStateScene::UpgradeUnit(gtuint uiUnitIndex, GnINumberLabel* pTotalMoneyLabel, GnINumberLabel* pUnitMoneyLabel)
{
	if( uiUnitIndex == -1 )
		return;
	
	GUserHaveItem* haveItem = GetCurrentHaveItem();
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();	
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	
	// check upgrade money
	guint32 itemLevel = haveItem->GetItemLevel( uiUnitIndex );
	
	if( MAX_UNIT_LEVEL <= itemLevel )
	{
		haveItem->Close();
		return;
	}
	
	guint32 buyMoney = GetItemInfo()->GetBuyPrice( uiUnitIndex, itemLevel );
	if( playingData->GetMoneyCount() < buyMoney )
	{
		haveItem->Close();
		return;	
	}

	itemLevel += 1;
	
	// update level
	haveItem->UpdateLevel( uiUnitIndex, itemLevel );
	
	// set money data
	guint32 money = playingData->GetMoneyCount() - buyMoney;
	playingData->SetMoneyCount( money );
	pTotalMoneyLabel->SetNumber( money );
	dataMng->SaveData();
	
	// set unit money label
	buyMoney = GetItemInfo()->GetBuyPrice( uiUnitIndex, itemLevel );
	pUnitMoneyLabel->SetNumber( buyMoney );
	
	
	haveItem->Close();
	
	
}

void GStateScene::UpdateItemCount(GUserHaveItem* pHaveItem, GnIListCtrl* pInvenList, GnIListCtrl* pEquipList
	, guint32 uiItemIndex, guint32 uiItemCount)
{
	
	pHaveItem->UpdateCount( uiItemIndex, uiItemCount );
	GItemListCtrlItem* item = GetListCtrlItemFromIndex( pInvenList, uiItemIndex );
	if( item )
		item->SetItemCount( uiItemCount );
	
	item = GetListCtrlItemFromIndex( pEquipList, uiItemIndex );
	if( item )
		item->SetItemCount( uiItemCount );	
}

GItemListCtrlItem* GStateScene::GetListCtrlItemFromIndex(GnIListCtrl* pList, guint32 uiIndex)
{
	for( gtuint i = 0 ; i < pList->GetColumnSize() ; i++ )
	{
		for( gtuint j = 0 ; j < pList->GetRowSize() ; j++ )
		{
			GItemListCtrlItem* item = (GItemListCtrlItem*)pList->GetItem( i , j );
			if( item && item->GetItemIndex() == uiIndex )
			{
				return item;
			}
		}
	}
	return NULL;
}