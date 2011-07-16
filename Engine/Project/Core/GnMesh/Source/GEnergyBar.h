//
//  GEnergyBar.h
//  Core
//
//  Created by Max Yoon on 11. 7. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GEnergyBar__
#define __Core__GEnergyBar__
#include "GnIButton.h"
#include "GnINumberLabel.h"

class GEnergyBar : public GnIButton
{
	static const gtuint msMaxDigit = 4;
private:
	float mFillTime;
	float mAcumTime;
	GnINumberLabel mLabelCurrentEnergy;
	GnINumberLabel mLabelMaxEnergy;
	
public:	
	static GEnergyBar* Create(gint32 uiMax, float fFillTime
	  , const gchar* pBackgroundImagePath = NULL);
	
public:
	void Init(gint32 uiMax, float fFillTime);
	void Update(float fDeltaTime);
	
public:
	inline GnINumberLabel* GetCurrentEnergyLabel() {
		return &mLabelCurrentEnergy;
	}
	inline GnINumberLabel* GetMaxEnergyLabel() {
		return &mLabelMaxEnergy;
	}
	inline gint32 GetCurrentEnergy() {
		return mLabelCurrentEnergy.GetNumber();
	}
	inline void SetCurrentEnergy(gint32 val) {
		mLabelCurrentEnergy.SetNumber( val );
	}
	inline guint32 GetMaxEnergy() {
		return mLabelMaxEnergy.GetNumber();
	}
	inline void SetMaxEnergy(gint32 iMaxEnergy) {
		mLabelMaxEnergy.SetNumber( iMaxEnergy );
	}
	
protected:
	GEnergyBar(const gchar* pBackgroundImagePath);
	void SetPosition(GnVector2& cPos);
};

#endif
