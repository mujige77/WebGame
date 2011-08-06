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
	: GnIButton( pcBackgroundImage ), mpNumberString( NULL ), mNumber( 0 )
{
	SetMaxDigit( uiMaxDigit );
	SetIsDisableCantpushBlind( true );
	SetIsCantPush( true );
}

GnINumberLabel::~GnINumberLabel()
{
	if( mpNumberString )
		GnFree( mpNumberString );
}

void GnINumberLabel::Init(const gchar* pLabel, const gchar* pcNumberFontFilePath, gint iItemWidth
	, gint iItemHeight, char startCharMap)
{
	mpLabel = CCLabelAtlas::labelWithString( pLabel, pcNumberFontFilePath, iItemWidth, iItemHeight
		, startCharMap );
	mpLabel->setAnchorPoint( CCPointMake( 0.5f, 0.5f ) );
	AddToParentNode( mpLabel );
	SetContentSize( iItemWidth, iItemHeight );
}
