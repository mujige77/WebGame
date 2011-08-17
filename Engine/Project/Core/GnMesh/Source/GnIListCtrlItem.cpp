//
//  GnIListCtrlItem.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 27..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnInterfacePCH.h"
#include "GnIListCtrlItem.h"

GnImplementRTTI(GnIListCtrlItem, GnIButton);

GnIListCtrlItem::GnIListCtrlItem(const gchar* pcDefaultImage, const gchar* pcClickImage
	, const gchar* pcDisableImage, eButtonType eDefaultType) : GnIButton( pcDefaultImage, pcClickImage
	, pcDisableImage, eDefaultType ), mEmptyItem( false )
{
	
}

GnIListCtrlItem::~GnIListCtrlItem()
{
}

bool GnIListCtrlItem::PushUp(float fPointX, float fPointY)
{
	return GnInterface::PushUp( fPointX, fPointY );
}

bool GnIListCtrlItem::PushMove(float fPointX, float fPointY)
{
	return GnIButton::PushMove( fPointX, fPointY );
}

void GnIListCtrlItem::Push()
{
	GnIButton::Push();
}

void GnIListCtrlItem::PushUp()
{
	GnIButton::PushUp();
}
