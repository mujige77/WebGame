//
//  GnNumberLabel.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GnINumberLabel.h"

GnINumberLabel::GnINumberLabel(const gchar* pcBackgroundImage, guint32 uiMaxDigit)
	: GnIButton( pcBackgroundImage ), mNumberString( NULL ), mNumber( 0 )
{
	SetMaxDigit( uiMaxDigit );
	SetIsDisableCantpushBlind( true );
	SetIsCantPush( true );
}

void GnINumberLabel::Init(const gchar* pLabel, const gchar* pcNumberFontFilePath, gint iItemWidth
	, gint iItemHeight, char startCharMap)
{
	mpLabel = CCLabelAtlas::labelWithString( pLabel, pcNumberFontFilePath, iItemWidth, iItemHeight
		, startCharMap );
	AddToParentNode( mpLabel );
}
