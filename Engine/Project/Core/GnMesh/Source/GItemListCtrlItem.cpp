#include "GnGamePCH.h"
#include "GItemListCtrlItem.h"

GnImplementRTTI(GItemListCtrlItem, GStateListCtrlItem);

GItemListCtrlItem::GItemListCtrlItem(const gchar* pcDefaultImage, const gchar* pcClickImage
	, const gchar* pcDisableImage, eButtonType eDefaultType) : GStateListCtrlItem( pcDefaultImage
	, pcClickImage, pcDisableImage, eDefaultType ), mCreateLabelPrice( false )
{
	gstring fullPath;
	GetFullPathFromWorkPath( "Upgrade/items/1234.png", fullPath );
	
	mItemCount.Init( "1", fullPath.c_str(), 6, 8, '.' );
	SetItemCount( 1 );
	AddInterfaceToParentNode( &mItemCount, INTERFACE_ZORDER + 1 );
}

void GItemListCtrlItem::CreateLabelPrice()
{
	gstring fullPath;
	GetFullPathFromWorkPath( "Upgrade/items/1234.png", fullPath );
	
	mLabelPrice.Init( "0", fullPath.c_str(), 6, 8, '.' );
	SetPrice( 0 );
	AddInterfaceToParentNode( &mLabelPrice, INTERFACE_ZORDER + 1 );
	
	mCreateLabelPrice = true;
}

void GItemListCtrlItem::CreateIconMoney()
{
	mpsIconMoney = GnNew GnInterface( "Upgrade/items/325_176.png" );
	AddInterfaceToParentNode( mpsIconMoney, INTERFACE_ZORDER + 1 );	
}

void GItemListCtrlItem::SetPosition(GnVector2& cPos)
{
	GnIListCtrlItem::SetPosition( cPos );
	
	GnVector2 pos = cPos;
	pos.y -= 20.0f;
	if( mCreateLabelPrice )
		mLabelPrice.SetPosition( pos );
	
	if( mpsIconMoney )
	{
		pos.x -= 20.0f;
		mpsIconMoney->SetPosition( pos );
	}
	
	pos = cPos;
	if( mCreateLabelPrice )		
		pos.y -= 6.0f;
	else
		pos.y -= 12.0f;
	pos.x += 11.0f;
	mItemCount.SetPosition( pos );
}