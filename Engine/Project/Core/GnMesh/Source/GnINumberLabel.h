//
//  GnNumberLabel.h
//  Core
//
//  Created by Max Yoon on 11. 7. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GnNumberLabel__
#define __Core__GnNumberLabel__

#include "GnIButton.h"
class GnINumberLabel : public GnIButton
{
private:
	guint32 mMaxDigit;
	const gchar* mHoldDigitString;
	gint32 mNumber;
	gchar* mpNumberString;
	CCLabelAtlas* mpLabel;
	
public:
	GnINumberLabel(const gchar* pcBackgroundImage = NULL, guint32 uiMaxDigit = 3);
	virtual ~GnINumberLabel();
	void Init(const gchar* pLabel, const gchar* pcNumberFontFilePath, gint iItemWidth
		, gint iItemHeight, char startCharMap);
public:
	void SetPosition(GnVector2& cPos) {
		GnIButton::SetPosition( cPos );
		mpLabel->setPosition( CCPointMake( cPos.x, cPos.y ) );
	}
	
public:
	inline void SetMaxDigit(guint32 uiMaxDigit, const gchar* pDigitString = NULL) {
		mMaxDigit = uiMaxDigit;
		mHoldDigitString = pDigitString;
		if( mpNumberString )
			GnFree( mpNumberString );		
		mpNumberString = GnAlloc( gchar, uiMaxDigit+2 );
	}
	inline gint32 GetNumber() {
		return mNumber;
	}
	inline const gchar* GetNumberString() {
		return mpNumberString;
	}
	inline void SetNumber(gint32 iNumber) {
		if( mHoldDigitString )
			GnSprintf( mpNumberString, sizeof(gchar) * mMaxDigit+2, mHoldDigitString, iNumber );
		else
			GnSprintf( mpNumberString, sizeof(gchar) * mMaxDigit+2, "%d", iNumber );
		mNumber = iNumber;
		mpLabel->setString( mpNumberString );
	}
};

#endif
