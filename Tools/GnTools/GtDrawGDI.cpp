#include "StdAfx.h"
#include "GtDrawGDI.h"


GtDrawGDI::GtDrawGDI(void) : mPen( Color( 255, 255, 0), 1.0f )
{
}


GtDrawGDI::~GtDrawGDI(void)
{
}

void GtDrawGDI::Draw(CDC *pDC,int nSx,int nSy, int iWidth, int iHeight)
{
	if( pDC->GetSafeHdc() == NULL )
		return;	
	
	Graphics griphics( pDC->GetSafeHdc() );
	DoDraw( griphics, nSx, nSy, iWidth, iHeight );
}

void GtDrawGDI::Draw(CDC *pDC, Gdiplus::Rect Rect)
{
	if( pDC->GetSafeHdc() == NULL )
		return;
	Graphics griphics( pDC->GetSafeHdc() );	
	DoDraw( griphics, Rect.X, Rect.Y, Rect.Width, Rect.Height );
	
}

void GtDrawGDI::Draw(HDC pDC,int nSx,int nSy,int iWidth, int iHeight)
{
	if( pDC == NULL )
		return;
	Graphics griphics( pDC );	
	DoDraw( griphics, nSx, nSy, iWidth, iHeight );
}

void GtDrawGDI::Draw(HDC pDC, Gdiplus::Rect Rect)
{
	if( pDC == NULL )
		return;	

	Graphics griphics( pDC );
	DoDraw( griphics, Rect.X, Rect.Y, Rect.Width, Rect.Height );
}