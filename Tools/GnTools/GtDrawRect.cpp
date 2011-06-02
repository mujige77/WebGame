#include "StdAfx.h"
#include "GtDrawRect.h"


GtDrawRect::GtDrawRect(void)
{
}


GtDrawRect::~GtDrawRect(void)
{
}

void GtDrawRect::DoDraw(Graphics& graphics,int iStartx,int iStarty,int iWidth, int iHeight)
{
	Pen pen( Color( 255, 255, 0), 1.0f );
	graphics.DrawRectangle( &pen, iStartx, iStarty, iWidth, iHeight );
}