#include "GnGamePCH.h"
#include "GStateListCtrlItem.h"

GnImplementRTTI(GStateListCtrlItem, GnIListCtrlItem);

GStateListCtrlItem::GStateListCtrlItem(const gchar* pcDefaultImage, const gchar* pcClickImage
	, const gchar* pcDisableImage, eButtonType eDefaultType) : GnIListCtrlItem( pcDefaultImage
	, pcClickImage, pcDisableImage, eDefaultType ), mpItemExplain( NULL )
{
	SetIsHidePushDefaultButton( false );
	SetIsHidePushUpClickButton( false );
}

GStateListCtrlItem::~GStateListCtrlItem()
{
//	if( mpItemExplain )
//		mpExplainParent->RemoveChild( mpItemExplain );
}