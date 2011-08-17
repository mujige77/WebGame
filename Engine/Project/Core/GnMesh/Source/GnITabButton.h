//
//  GnITabButton.h
//  Core
//
//  Created by Max Yoon on 11. 7. 25..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GnITabButton_h
#define Core_GnITabButton_h

class GnITabPage;
class GnITabButton : public GnIButton
{
private:
	GnITabPage* mpTabPage;
	
public:
	GnITabButton(GnITabPage* pTabPage, const gchar* pcDefaultImage, const gchar* pcClickImage = NULL
			  , const gchar* pcDisableImage = NULL, eButtonType eDefaultType = TYPE_NORMAL);
	virtual ~GnITabButton();
	
public:
	virtual bool PushUp(float fPointX, float fPointY);
	virtual bool PushMove(float fPointX, float fPointY);
	virtual void Push();
	virtual void PushUp();
	virtual void SetVisibleNormal(bool val){};
public:
	inline GnITabPage* GetTabPage() {
		return mpTabPage;
	}
};

#endif
