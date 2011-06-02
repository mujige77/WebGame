#pragma once
#include "GtDrawGDI.h"

class GtDrawRect : public GtDrawGDI
{
public:
	GtDrawRect(void);
	~GtDrawRect(void);

protected:
	virtual void DoDraw(Graphics& graphics,int iStartx,int iStarty,int iWidth, int iHeight);
};

