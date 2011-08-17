#include "GnGamePCH.h"
#include "GAbilityListCtrlItem.h"

GnImplementRTTI(GAbilityListCtrlItem, GStateListCtrlItem);



GAbilityListCtrlItem::GAbilityListCtrlItem(const gchar* pcDefaultImage, const gchar* pcClickImage
	, const gchar* pcDisableImage, eButtonType eDefaultType) : GStateListCtrlItem( pcDefaultImage
	, pcClickImage, pcDisableImage, eDefaultType )
{	
	gstring fullPath;
	GetFullPathFromWorkPath( "Upgrade/stet/a 104_87.png", fullPath );
	
	mLabelCurrentLevel.Init( "0", fullPath.c_str(), 10, 13, '.' );
	//mLabelCurrentLevel.SetMaxDigit( 2, "%02d" );
	SetCurrentLevel( 0 );
	
	mLabelMaxLevel.Init( "20", fullPath.c_str(), 10, 13, '.' );
	//mLabelMaxLevel.SetMaxDigit( 2, "%02d" );
	SetMaxLevel( 20 );
	
	
	GetParentUseNode()->addChild( mLabelCurrentLevel.GetParentUseNode(), INTERFACE_ZORDER + 1 );
	GetParentUseNode()->addChild( mLabelMaxLevel.GetParentUseNode(), INTERFACE_ZORDER + 1 );
}

void GAbilityListCtrlItem::SetPosition(GnVector2& cPos)
{
	GnIListCtrlItem::SetPosition( cPos );
	
	GnVector2 numLabelPos = cPos;
	numLabelPos.x += 20.0f;
	numLabelPos.y += 7.0f;
	mLabelCurrentLevel.SetPosition( numLabelPos );
	
	numLabelPos.y -= 18.0f;
	mLabelMaxLevel.SetPosition( numLabelPos );
}
