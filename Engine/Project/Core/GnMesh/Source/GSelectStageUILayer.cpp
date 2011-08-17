//
//  GSelectStageLayer.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 28..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GSelectStageUILayer.h"
#include "GnIListPageCtrl.h"

void GSelectStageUILayer::CreateListCtrlItem(guint32 uiLastStage)
{
	gtuint numPageItem = mpListCtrl->GetColumnSize() * mpListCtrl->GetRowSize();
	gtuint numRow = mpListCtrl->GetRowSize();
	gtuint numColumn = mpListCtrl->GetColumnSize();
	for( gtuint i = 0; i < mpListCtrl->GetPageSize(); i++ )
	{
		for ( gtuint k = 0 ; k < numRow; k++ )
		{
			for ( gtuint j = 0; j < numColumn; j++ )
			{
				//	gtuint col =( uiNumItem / 3 ) % NUM_COLUMN;
				//	row = uiNumItem % NUM_ROW;	
				// guint32 numCurrentItem = ( i * numPageItem ) + ( ( j * numRow ) + k );
				guint32 numCurrentItem = ( i * numPageItem ) + ( ( k * numColumn ) + j );
				GnIListCtrlItem* item = NULL;
				if( uiLastStage < numCurrentItem )
					item = CreateListCtrlItem( 0, false );
				else if( uiLastStage == numCurrentItem )
					item = CreateListCtrlItem( 0, true );
				else
					item = CreateListCtrlItem( 1, true );
				mpListCtrl->SetItem( i, j, k, item );
			}
		}
	}
}

GnInterfaceGroup* GSelectStageUILayer::CreateInterface(gtuint uiIndex
	, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot)
{
	GnInterfaceGroup* pGroup = NULL;
	switch (uiIndex)
	{
		case UI_SELECTSTAGE_LIST:
		{
			pGroup = CreateListCrl();
		}
		break;
		case UI_SELECTSTAGE_BT:
		{
			pGroup = CreateSelectStageButtons();
		}
		break;
	}
	if( pGroup )
		pGroup->SubscribeClickedEvent( pSlot );
	return pGroup;
}

void GSelectStageUILayer::Update(float fTime)
{
	mpListCtrl->Update( fTime );
}

GnInterfaceGroup* GSelectStageUILayer::CreateListCrl()
{
	mpListCtrl = GnIListPageCtrl::CreateListCtrl( GnVector2( 31.0f, 72.0f ), GnVector2( 455.0f, 290.0f )
		, NUM_PAGE, NUM_COLUMN, NUM_ROW, 71.0f, 72.0f );
	
	mpListCtrl->SetPage( 0 );
	mpListCtrl->SetRect( 31.0f, 72.0f, 455.0f, 290.0f );
	AddChild( mpListCtrl, INTERFACE_ZORDER );
	return mpListCtrl;
}

GnInterfaceGroup* GSelectStageUILayer::CreateSelectStageButtons()
{
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();
	
	GnIButton* buttons = NULL;
	GnInterface* label = NULL;
	// add buttons
	buttons = GnNew GnIButton( "StageScene/44_22.png", "StageScene/44_22 a.png", NULL );
	SetUIPosition( buttons, 44.0f, 22.0f );
	group->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StageScene/361_22.png", "StageScene/361_22 a.png", NULL );
	SetUIPosition( buttons, 361.0f, 22.0f );
	group->AddChild( buttons );
	
	buttons = GnNew GnIButton( "StageScene/13_285.png", NULL, NULL );
	SetUIPosition( buttons, 13.0f, 285.0f );
	group->AddChild( buttons );
	group->AddPersonalChild( buttons );
	
	label = GnNew GnInterface( "StageScene/124_22.PNG" );
	SetUIPosition( label, 124.0f, 22.0f );
	group->AddChild( label );
	
	group->SetRect( 44.0f, 22.0f, 450.0f, 60.0f );
	AddChild( group, INTERFACE_ZORDER );
	
	mpButtonGroup = group;	
	return group;
}

GnIListCtrlItem* GSelectStageUILayer::CreateListCtrlItem(guint32 uiStarCount, bool isEnable)
{
//	gtuint col =( uiNumItem / 3 ) % NUM_COLUMN;
//	gtuint row = uiNumItem % NUM_ROW;
//	GnIListCtrlItem* listItme = NULL;
//	if( col < 1 && row < 1 )
//	{
//		listItme = GnNew GnIListCtrlItem( "StageScene/31_72 a.png", NULL, "StageScene/31_72 c.png" );
//	}
//	else
//	{
//		listItme = GnNew GnIListCtrlItem( "StageScene/31_72 a.png", NULL, "StageScene/31_72 c.png"
//										 , GnIButton::TYPE_DISABLE );			
//	}
//	return listItme;
	
	GnIListCtrlItem* listItme = NULL;
	if( isEnable )
	{
		if( uiStarCount )
			listItme = GnNew GnIListCtrlItem( "StageScene/31_72 b.png", NULL, NULL );
		else
			listItme = GnNew GnIListCtrlItem( "StageScene/31_72 a.png", NULL, NULL );
	}
	else
	{
		listItme = GnNew GnIListCtrlItem( NULL, NULL, "StageScene/31_72 c.png"
			, GnIButton::TYPE_DISABLE );			
	}
	return listItme;
}