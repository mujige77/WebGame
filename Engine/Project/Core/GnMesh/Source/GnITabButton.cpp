//
//  GnITabButton.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 25..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GnITabButton.h"
#include "GnITabPage.h"

GnITabButton::GnITabButton(GnITabPage* pTabPage, const gchar* pcDefaultImage, const gchar* pcClickImage
	, const gchar* pcDisableImage, eButtonType eDefaultType) : GnIButton( pcDefaultImage, pcClickImage
	, pcDisableImage, eDefaultType ), mpTabPage( pTabPage )
{
	
}

GnITabButton::~GnITabButton()
{
}

bool GnITabButton::PushUp(float fPointX, float fPointY)
{
	return false;
}

bool GnITabButton::PushMove(float fPointX, float fPointY)
{
	return false;
}

void GnITabButton::Push()
{
	GnIButton::Push();
	SubPushCount();
	mpTabPage->SetIsVisible( true );	
}

void GnITabButton::PushUp()
{
	GnIButton::PushUp();
	mpTabPage->SetIsVisible( false );
}
