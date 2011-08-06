//
//  GIconGage.h
//  Core
//
//  Created by Max Yoon on 11. 7. 19..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GIconGage__
#define __Core__GIconGage__

#include "GnInterface.h"
#include "GnIProgressBar.h"

class GIconGage
{
public:
	GIconGage() : mpIcon( NULL ), mpGage( NULL )
	{}
public:
	GnInterface* mpIcon;
	GnIProgressBar* mpGage;
};

static GIconGage CreateIconGage(GnIProgressBar::eProgressType eType, const gchar* pcIconName
	, const gchar* pcProgress, const gchar* pcProgressGage)
{
	GIconGage gage;
	GnInterface* icon;
	GnIProgressBar* gageBar;
	
	gageBar = GnIProgressBar::Create( eType, pcProgress, pcProgressGage );
	
	if( gageBar == NULL )
		return gage;
	
	if( gageBar )
	{
		gageBar->SetVisibleProgress( true );
		gageBar->SetVisibleBackground( true );
	}
	
	icon = GnNew GnInterface();
	if( icon->CreateDefaultImage( pcIconName ) == false )
	{
		return gage;
	}
//	float pointX = 0;
//	float pointY = 0;
//	GnVector2 vec = menu->GetContentSize();	
//	menu->SetUIPoint( pointX, pointY );	
//	menu->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	gage.mpIcon = icon;
	gage.mpGage = gageBar;
	return gage;
}

#endif
