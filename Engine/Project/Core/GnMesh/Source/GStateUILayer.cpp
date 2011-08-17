#include "GnGamePCH.h"
#include "GStateUILayer.h"
#include "GnITabCtrl.h"
#include "GnIListCtrl.h"
#include "GnIButton.h"
#include "GnINumberLabel.h"
#include "GAbilityListCtrlItem.h"
#include "GItemListCtrlItem.h"
#include "GItemInfo.h"
#include "GGameDefine.h"
#include "GPlayingDataManager.h"
#include "GUserHaveItem.h"

GStateUILayer::GStateUILayer() : mpTabCtrl( NULL )
{
	
}

GStateUILayer::~GStateUILayer()
{
	
}

GnInterfaceGroup* GStateUILayer::CreateInterface(gtuint uiIndex
	, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot)
{
	GnInterfaceGroup* pGroup = NULL;
	switch (uiIndex)
	{
		case UI_STATE_UNITTAB:
		{
			// create unit upgrade tabpage
			GnITabPage* pTabPage = CreateUnitPage();
			GnVector2 tabctrlSize = pTabPage->GetContentSize();
			
			// createtabctrl
			CreateTabCtrl( tabctrlSize );
			mpTabCtrl->AddTabCreateButtonImage( pTabPage, "Upgrade/upgrade/51_18.png", NULL );
			pGroup = pTabPage;
			mpTabCtrl->SetActiveTab( 0 );
		}
		break;
		case UI_STATE_SHOPTAB:
		{
			// create items
			GnITabPage* pTabPage = CreateItemPage();
			mpTabCtrl->AddTabCreateButtonImage( pTabPage, "Upgrade/items/211_18.png", NULL );
			mpShopListCtrl->SubscribeClickedEvent( pReceiveSlot );
			mpInventoryListCtrl->SubscribeClickedEvent( pReceiveSlot );
			mpEquipListCtrl->SubscribeClickedEvent( pReceiveSlot );
			pGroup = pTabPage;
		}
		break;
		case UI_STATE_ABILITYTAB:
		{
			
			// create New tab page
			GnITabPage* pTabPage = CreateAbilityPage();
			mpTabCtrl->AddTabCreateButtonImage( pTabPage, "Upgrade/stet/131_18.png", NULL );
			mpAbilityListCtrl->SubscribeClickedEvent( pReceiveSlot );
			pGroup = pTabPage;
		}
		break;
		case UI_STATE_OTHERUI:
		{	
			pGroup = CreateOtherUI();
		}
		break;
	}
	
	if( pGroup )
		pGroup->SubscribeClickedEvent( pReceiveSlot );
	return pGroup;
}

void GStateUILayer::Update(float fTime)
{
	if( mpTabCtrl )
		mpTabCtrl->Update( fTime );
	
	if( mpAbilityListCtrl )
		mpAbilityListCtrl->Update( fTime );
}
GItemListCtrlItem* GStateUILayer::CreateItemCtrlItem(gtuint uiIndex)
{
	GnITabPage* page = mpTabCtrl->GetTabPage( ITEM_TAB );
	return CreateItemCtrlItem( uiIndex, page );
}

GItemListCtrlItem* GStateUILayer::CreateItemCtrlItem(gtuint uiIndex, GnInterface* pExplainParent)
{
	if( GItemInfo::mscNumMaxItem <= uiIndex  )
		return NULL;
	GnInterface* explian = GnNew GnInterface( GetItemInfo()->GetExplainFileName( uiIndex ) );
	SetUIPosition( explian, 28.0f, 222.0f );
	explian->SetIsVisible( false );			
	pExplainParent->AddChild( explian, INTERFACE_ZORDER );
	
	GItemListCtrlItem* item = GnNew GItemListCtrlItem( GetItemInfo()->GetPriceIconFileName( uiIndex ) );
	item->CreateLabelPrice();
	item->SetItemExplain( pExplainParent, explian );
	item->SetPrice( GetItemInfo()->GetBuyPrice( uiIndex ) );
	item->SetItemIndex( uiIndex + INDEX_ITEM );
	return item;
}

GItemListCtrlItem* GStateUILayer::CreateEquipCtrlItem(gtuint uiIndex)
{
	GnITabPage* page = mpTabCtrl->GetTabPage( ITEM_TAB );
	return CreateEquipCtrlItem( uiIndex, page );	
}

GItemListCtrlItem* GStateUILayer::CreateEquipCtrlItem(gtuint uiIndex, GnInterface* pExplainParent)
{
	if( GItemInfo::mscNumMaxItem <= uiIndex  )
		return NULL;
	GnInterface* explian = GnNew GnInterface( GetItemInfo()->GetExplainFileName( uiIndex ) );
	SetUIPosition( explian, 28.0f, 222.0f );
	explian->SetIsVisible( false );			
	pExplainParent->AddChild( explian, INTERFACE_ZORDER );
	
	GItemListCtrlItem* item = GnNew GItemListCtrlItem( GetItemInfo()->GetIconFileName( uiIndex )
		, "Upgrade/items/400_174 s.png" );
	
	item->SetItemExplain( pExplainParent, explian );
	//item->SetPrice( GetItemInfo()->GetBuyPrice( uiIndex ) );
	item->SetItemIndex( uiIndex + INDEX_ITEM );
	return item;	
}

GnITabCtrl* GStateUILayer::CreateTabCtrl(GnVector2& cTabctrlSize)
{
	mpTabCtrl = GnITabCtrl::CreateTabCtrl( cTabctrlSize.x, cTabctrlSize.y, 30.0f, -3.8f );
	mpTabCtrl->SetIsEnablePushMove( true );	
	
	GnInterface* pBlind = GnNew GnInterface( "Upgrade/1.png" );
	SetUIPosition( pBlind, 0.0f, 0.0f );
	
	mpTabCtrl->AddChild( pBlind, INTERFACE_ZORDER );
	
	mpTabCtrl->SetUIPoint( 11.0f, 41.0f );
	mpTabCtrl->SetRect( 14.0f, 43.0f - 25.0f, 14.0f + cTabctrlSize.x, 43.0f - 25.0f + cTabctrlSize.y );
	AddChild( mpTabCtrl );
	return mpTabCtrl;
}

GnITabPage* GStateUILayer::CreateUnitPage()
{
	GnITabPage* pTabPage = GnNew GnITabPage( "Upgrade/upgrade/11_41.png" );
	GnInterfaceGroup* unitGroup = pTabPage;//GnNew GnInterfaceGroup();
	const gint32 buttonZorder = INTERFACE_ZORDER + 1;
	GnIButton* buttons = GnNew GnIButton( "Upgrade/upgrade/32_74.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );	
	buttons->SetTegID( BT_UPC1 );
	SetUIPosition( buttons, 32.0f, 74.0f );
	unitGroup->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/upgrade/82_74.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC2 );
	SetUIPosition( buttons, 82.0f, 74.0f );
	unitGroup->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/upgrade/132_74.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC3 );
	SetUIPosition( buttons, 132.0f, 74.0f );
	unitGroup->AddChild( buttons, buttonZorder );

	buttons = GnNew GnIButton( "Upgrade/upgrade/182_74.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC4 );
	SetUIPosition( buttons, 182.0f, 74.0f );
	unitGroup->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/upgrade/232_74.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC5 );
	SetUIPosition( buttons, 232.0f, 74.0f );
	unitGroup->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/upgrade/32_124.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC6 );
	SetUIPosition( buttons, 32.0f, 124.0f );
	unitGroup->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/upgrade/82_124.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC7 );
	SetUIPosition( buttons, 82.0f, 124.0f );
	unitGroup->AddChild( buttons, buttonZorder );

	buttons = GnNew GnIButton( "Upgrade/upgrade/132_124.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC8 );
	SetUIPosition( buttons, 132.0f, 124.0f );
	unitGroup->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/upgrade/182_124.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC9 );
	SetUIPosition( buttons, 182.0f, 124.0f );
	unitGroup->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/upgrade/232_124.png", "Upgrade/upgrade/80_124.png" );
	buttons->SetIsHidePushDefaultButton( false );
	buttons->SetIsHidePushUpClickButton( false );
	buttons->SetTegID( BT_UPC10 );
	SetUIPosition( buttons, 232.0f, 124.0f );
	unitGroup->AddChild( buttons, buttonZorder );
	unitGroup->SetRect( 30.0f, 80.0f, 275.0f, 180.0f );


	//pTabPage->AddChild( unitGroup, buttonZorder );
	
	// upgrade button
	buttons = GnNew GnIButton( "Upgrade/upgrade/315_204 on.png", "Upgrade/upgrade/315_204 off.png" );
	buttons->SetTegID( BT_UNIT_UPGRADE );
	SetUIPosition( buttons, 315.0f, 204.0f );
	
	pTabPage->AddChild( buttons, buttonZorder );
	
	// money
	GnInterface* iconMoney = GnNew GnInterface( "Upgrade/upgrade/325_176.png" );
	SetUIPosition( iconMoney, 325.0f, 176.0f );
	pTabPage->AddChild( iconMoney, buttonZorder );
	
	gstring fullPath;
	GetFullPathFromWorkPath( "Upgrade/upgrade/352_176.png", fullPath );
	
	GnINumberLabel* label = GnNew GnINumberLabel( NULL, 10 );
	label->Init( "0", fullPath.c_str(), 12, 14, '.' );
	SetUIPosition( label, 352.0f, 176.0f );	
	pTabPage->AddChild( label, buttonZorder );
	return pTabPage;
}

GnITabPage* GStateUILayer::CreateAbilityPage()
{
	GnITabPage* pTabPage = GnNew GnITabPage( "Upgrade/stet/11_41.png" );
	pTabPage->SetIsEnablePushMove( true );	
	
	mpAbilityListCtrl = GnIListCtrl::CreateListCtrl( GnVector2(40.0f, 77.0f), NUM_STET_COLUMN, NUM_STET_ROW
												 , 110.0f, 60.0f );
	mpAbilityListCtrl->SetRect( 40.0f, 77.0f, 40.0f + 350.0f, 77.0f + 125.0f );
	mpAbilityListCtrl->SetMoveType( GnIListCtrl::eMoveUpDown, 3, 2 );
	pTabPage->AddChild( mpAbilityListCtrl, INTERFACE_ZORDER - 2 );
	
	GnInterface* pListCtrlBack = GnNew GnInterface( "Upgrade/stet/31_67.png" );
	SetUIPosition( pListCtrlBack, 31.0f, 70.0f );
	pTabPage->AddChild( pListCtrlBack, INTERFACE_ZORDER - 3 );	
	
	// upgrade button
	GnIButton* buttons = GnNew GnIButton( "Upgrade/stet/387_124 on.png", "Upgrade/stet/398_77 off.png" );
	buttons->SetTegID( BT_ABILITY_UPGRADE );
	SetUIPosition( buttons, 387.0f,	124.0f );
	pTabPage->AddChild( buttons, INTERFACE_ZORDER );
	
	// star label
	GnInterface* label = GnNew GnInterface( "Upgrade/stet/398_77.png" );
	SetUIPosition( label, 401.0f, 77.0f );
	pTabPage->AddChild( label, INTERFACE_ZORDER );
	
	// create list ctrl item
	CreateBasicAbilityCtrlItem( pTabPage );
	
	return pTabPage;
}

GnITabPage* GStateUILayer::CreateItemPage()
{
	const gint32 buttonZorder = INTERFACE_ZORDER + 1;
	GnITabPage* pTabPage = GnNew GnITabPage( "Upgrade/items/11_41.png" );
	pTabPage->SetIsEnablePushMove( true );
		
	mpShopListCtrl = GnIListCtrl::CreateListCtrl( GnVector2(32.0f, 77.0f), NUM_ITEMSHOP_COLUMN, NUM_ITEMSHOP_ROW
		, 51.0f, 62.0f );
	mpShopListCtrl->SetRect( 32.0f, 77.0f, 32.0f + 150.0f, 77.0f + 130.0f );
	mpShopListCtrl->SetMoveType( GnIListCtrl::eMoveUpDown, 3, 2 );
	pTabPage->AddChild( mpShopListCtrl, INTERFACE_ZORDER - 2 );
	
	mpInventoryListCtrl = GnIListCtrl::CreateListCtrl( GnVector2(242.0f, 77.0f), 2, 0, 51.0f, 62.0f );
	mpInventoryListCtrl->SetRect( 240.0f, 77.0f, 240.0f + 110.0f, 77.0f + 130.0f );
	mpInventoryListCtrl->SetMoveType( GnIListCtrl::eMoveUpDown, 2, 2 );
	//mpInventoryListCtrl->SetEmptyItemFileName( "Upgrade/items/134_140.png" );
	pTabPage->AddChild( mpInventoryListCtrl, INTERFACE_ZORDER - 2 );	
	
	mpEquipListCtrl = GnIListCtrl::CreateListCtrl( GnVector2( 400.0f, 78.0f), 1, 3, 48.0f, 48.0f );
	mpEquipListCtrl->SetRect( 401.0f, 78.0f, 401.0f + 70.0f, 78.0f + 133.0f );
	//mpEquipListCtrl->SetEmptyItemFileName( "Upgrade/items/400_124 a.png" );
	pTabPage->AddChild( mpEquipListCtrl, INTERFACE_ZORDER - 2 );
	
	
	// list background
	GnInterface* pListCtrlBack = GnNew GnInterface( "Upgrade/items/28_73.png" );
	SetUIPosition( pListCtrlBack, 28.0f, 76.0f );
	pTabPage->AddChild( pListCtrlBack, INTERFACE_ZORDER - 3 );	
	pListCtrlBack = GnNew GnInterface( "Upgrade/items/237_73.png" );
	SetUIPosition( pListCtrlBack, 237.0f, 76.0f );
	pTabPage->AddChild( pListCtrlBack, INTERFACE_ZORDER - 3 );	
	pListCtrlBack = GnNew GnInterface( "Upgrade/items/398_73.png" );
	SetUIPosition( pListCtrlBack, 398.0f, 76.0f );
	pTabPage->AddChild( pListCtrlBack, INTERFACE_ZORDER - 3 );	
	
	// create arrow
	GnIButton* buttons = GnNew GnIButton( "Upgrade/items/195_71 a.png", "Upgrade/items/195_71 b.png" );
	buttons->SetTegID( BT_SELL_ITEM );
	SetUIPosition( buttons, 195.0f,	74.0f );
	pTabPage->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/items/195_191 a.png", "Upgrade/items/195_191 b.png" );
	buttons->SetTegID( BT_BUY_ITEM );
	SetUIPosition( buttons, 195.0f,	159.0f );	
	pTabPage->AddChild( buttons, buttonZorder );
	
	buttons = GnNew GnIButton( "Upgrade/items/356_71 a.png", "Upgrade/items/356_71 b.png" );
	buttons->SetTegID( BT_UNEQUIP_ITEM );
	SetUIPosition( buttons, 356.0f,	74.0f );	
	pTabPage->AddChild( buttons, buttonZorder );

	buttons = GnNew GnIButton( "Upgrade/items/356_191 a.png", "Upgrade/items/356_191 b.png" );
	buttons->SetTegID( BT_EQUIP_ITEM );
	SetUIPosition( buttons, 356.0f,	159.0f );	
	pTabPage->AddChild( buttons, buttonZorder );
	
//	// sell label
//	GnInterface* label = GnNew GnInterface( "Upgrade/items/195_71.png" );
//	SetUIPosition( label, 195.0f, 71.0f );
//	pTabPage->AddChild( label, buttonZorder );
//	
//	label = GnNew GnInterface( "Upgrade/items/195_191.png" );
//	SetUIPosition( label, 195.0f, 191.0f );
//	pTabPage->AddChild( label, buttonZorder );
//	
//	label = GnNew GnInterface( "Upgrade/items/356_71.png" );
//	SetUIPosition( label, 356.0f, 71.0f );
//	pTabPage->AddChild( label, buttonZorder );
//	
//	label = GnNew GnInterface( "Upgrade/items/356_191.png" );
//	SetUIPosition( label, 356.0f, 191.0f );
//	pTabPage->AddChild( label, buttonZorder );
	
	// create list ctrl item
	CreateBasicShopCtrlItem( pTabPage );
	CreateBasicInventoryCtrlItem( pTabPage );
	CreateBasicEquipCtrlItem( pTabPage );
	
	return pTabPage;
}

GnInterfaceGroup* GStateUILayer::CreateOtherUI()
{
	GPlayingData* playingData = GPlayingDataManager::GetSingleton()->GetPlayingPlayerData();
	
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();
	GnIButton* buttons = NULL;

	// next button
	buttons = GnNew GnIButton( "Upgrade/415_8.png", NULL, NULL );
	SetUIPosition( buttons, 415.0f, 3.0f );
	group->AddChild( buttons );
	
	// prev button
	buttons = GnNew GnIButton( "Upgrade/365_3.png", NULL, NULL );
	SetUIPosition( buttons, 365.0f, 3.0f );
	group->AddChild( buttons );
	
	// numberlabel
	gstring fullPath;
	GetFullPathFromWorkPath( "Upgrade/MoneyNumber.png", fullPath );	
	mStarLabel = GnNew GnINumberLabel( NULL, 5 );
	mStarLabel->Init( "0", fullPath.c_str(), 16, 20, '.' );
	mStarLabel->SetNumber( playingData->GetStarCount() );
	mStarLabel->SetTegID( LABEL_STATE_STAR );
	SetUIPosition( mStarLabel, 120.0f, 276.0f );
	group->AddChild( mStarLabel );
	
	mMoneyLabel = GnNew GnINumberLabel( NULL, 10 );
	mMoneyLabel->Init( "0", fullPath.c_str(), 16, 20, '.' );
	mMoneyLabel->SetNumber( playingData->GetMoneyCount() );
	mMoneyLabel->SetTegID( LABEL_STATE_MONEY );
	SetUIPosition( mMoneyLabel, 350.0f, 276.0f );
	group->AddChild( mMoneyLabel );
	
	group->SetRect( 365.0f, 8.0f, 458.0f, 39.0f );
	AddChild( group, INTERFACE_ZORDER + 1 );
	return group;
}

void GStateUILayer::CreateBasicAbilityCtrlItem(GnInterface* pExplainParent)
{
	GUserHaveItem* haveItem = GPlayingDataManager::GetSingleton()->GetPlayingHaveItem();
	GPlayingData* playingData = GPlayingDataManager::GetSingleton()->GetPlayingPlayerData();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );
	
	const char fileName[NUM_STET_ROW][NUM_STET_COLUMN][256] = 	
	{
		{ {"Upgrade/stet/a 40_77.png"}, {"Upgrade/stet/b 150_77.png"}, {"Upgrade/stet/c 260_77.png"} },
		{ {"Upgrade/stet/d 40_134.png"}, {"Upgrade/stet/e 150_134.png"}, {"Upgrade/stet/f 260_134.png"} },
		{ {"Upgrade/stet/g 40_191.png"}, {"Upgrade/stet/h 150_191.png"}, {"Upgrade/stet/i 260_191.png"} },
		{ {"Upgrade/stet/j 40_248.png"}, {"Upgrade/stet/k 150_248.png"}, {"Upgrade/stet/l 260_248.png"} },
		{ {"Upgrade/stet/m 40_305.png"}, {"Upgrade/stet/GabIcon.png"}, {"Upgrade/stet/GabIcon.png"} }
	};
	const char explianFileName[NUM_STET_ROW][NUM_STET_COLUMN][256] = 	
	{
		{ {"Upgrade/stet/a 40_212.png"}, {"Upgrade/stet/b 40_212.png"}, {"Upgrade/stet/c 40_212.png"} },
		{ {"Upgrade/stet/d 40_212.png"}, {"Upgrade/stet/e 40_212.png"}, {"Upgrade/stet/f 40_212.png"} },
		{ {"Upgrade/stet/g 40_212.png"}, {"Upgrade/stet/h 40_212.png"}, {"Upgrade/stet/i 40_212.png"} },
		{ {"Upgrade/stet/j 40_212.png"}, {"Upgrade/stet/k 40_212.png"}, {"Upgrade/stet/l 40_212.png"} },
		{ {"Upgrade/stet/m 40_212.png"}, {""}, {""} }
	};	
	gtuint rowSize = mpAbilityListCtrl->GetRowSize();
	gtuint columnSize = mpAbilityListCtrl->GetColumnSize();
	gtuint i = 0;
	for ( gtuint k = 0 ; k < rowSize; k++ )
	{
		for ( gtuint j = 0; j < columnSize; j++ )
		{
			guint32 itemIndex = i + INDEX_ABILITY;
			GAbilityListCtrlItem* item = GnNew GAbilityListCtrlItem( fileName[k][j], "Upgrade/stet/as 41_77.png" );
			item->SetItemIndex( itemIndex );
			mpAbilityListCtrl->SetItem( j, k, item );
			
			if( k == 4 && j == 2 )
				continue;
			
			GnInterface* explian = GnNew GnInterface( explianFileName[k][j] );
			SetUIPosition( explian, 40.0f, 212.0f );
			explian->SetIsVisible( false );			
			pExplainParent->AddChild( explian, INTERFACE_ZORDER );
			
			item->SetItemExplain( pExplainParent, explian );
			item->SetCurrentLevel( haveItem->GetItemLevel( itemIndex ) );
			++i;
		}
	}
	
	GnIListCtrlItem* item = mpAbilityListCtrl->GetItem( 1, 4 );
	if( item )
	{
		item->SetIsDisableCantpushBlind( true );
		item->SetIsCantPush( true );
	}
	item = mpAbilityListCtrl->GetItem( 2, 4 );
	if( item )
	{
		item->SetIsDisableCantpushBlind( true );
		item->SetIsCantPush( true );
	}
	
	haveItem->Close();
}

void GStateUILayer::CreateBasicShopCtrlItem(GnInterface* pExplainParent)
{
	gtuint rowSize = mpShopListCtrl->GetRowSize();
	gtuint columnSize = mpShopListCtrl->GetColumnSize();
	gtuint i = 0;
	for ( gtuint k = 0 ; k < rowSize; k++ )
	{
		for ( gtuint j = 0; j < columnSize; j++ )
		{			
			if( i == 5 )
				break;
			GItemListCtrlItem* item = CreateItemCtrlItem( i, pExplainParent );
			mpShopListCtrl->SetItem( j, k, item );
			item->SetTegID( LISTITEM_SHOP );
			++i;
		}
	}
}

void GStateUILayer::CreateBasicInventoryCtrlItem(GnInterface* pExplainParent)
{
	GUserHaveItem* haveItem = GPlayingDataManager::GetSingleton()->GetPlayingHaveItem();
	GPlayingData* playingData = GPlayingDataManager::GetSingleton()->GetPlayingPlayerData();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );
	
	GnList<GUserHaveItem::Item> haveItems;
	haveItem->GetItems( eItem, haveItems );
	
	GnListIterator<GUserHaveItem::Item> iter = haveItems.GetIterator();
	gtuint itemCount = 0;
	while( iter.Valid() )
	{
		gtuint res = itemCount % NUM_ITEMINVEN_COLUMN;
		if( res == 0 )
			mpInventoryListCtrl->AddRow();
			
		GUserHaveItem::Item& item = iter.Item();
		gtuint itemIndex = item.mIndex - INDEX_ITEM;		
		
		GItemListCtrlItem* listItem = CreateItemCtrlItem( itemIndex, pExplainParent );
//		if( itemIndex < GItemInfo::mscNumMaxItem )
//		{
//			GnInterface* explian = GnNew GnInterface( GetItemInfo()->GetExplainFileName( itemIndex ) );
//			SetUIPosition( explian, 28.0f, 222.0f );
//			explian->SetIsVisible( false );			
//			pExplainParent->AddChild( explian, INTERFACE_ZORDER );
//			listItem->SetItemExplain( pExplainParent, explian );
//		}
		
		listItem->SetTegID( LISTITEM_INVEN );
		gtuint numRow = itemCount / NUM_ITEMINVEN_COLUMN;
		mpInventoryListCtrl->SetItem( itemCount % NUM_ITEMINVEN_COLUMN, numRow, listItem );
		
		iter.Forth();
		++itemCount;
	}
	haveItem->Close();
}

void GStateUILayer::CreateBasicEquipCtrlItem(GnInterface* pExplainParent)
{
	GUserHaveItem* haveItem = GPlayingDataManager::GetSingleton()->GetPlayingHaveItem();
	GPlayingData* playingData = GPlayingDataManager::GetSingleton()->GetPlayingPlayerData();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );
	
	GnList<GUserHaveItem::Item> haveItems;
	haveItem->GetItems( eEquip, haveItems );	
	
	GnListIterator<GUserHaveItem::Item> iter = haveItems.GetIterator();
	gtuint itemCount = 0;
	while( iter.Valid() )
	{
		GUserHaveItem::Item& item = iter.Item();
		gtuint itemIndex = item.mIndex - INDEX_ITEM;
		GItemListCtrlItem* listItem = CreateEquipCtrlItem( itemIndex, pExplainParent );
		mpEquipListCtrl->AddItem( listItem );
		listItem->SetTegID( LISTITEM_EQUIP );
	
		iter.Forth();
		++itemCount;
		if( ENABLE_MAX_EQUIP <= itemCount )
			break;
	}	
	haveItem->Close();
}
