#include "StdAfx.h"
#include "GtDrawMouseRectangle.h"


GtDrawMouseRectangle::GtDrawMouseRectangle(void)
{
}


GtDrawMouseRectangle::~GtDrawMouseRectangle(void)
{
}

void GtDrawMouseRectangle::Draw(CDC* pDC)
{
	GtDrawRect::Draw( pDC, mDrawRect.X, mDrawRect.Y, mDrawRect.Width
		, mDrawRect.Height );
}

void GtDrawMouseRectangle::SetStartPoint(int iX, int iY)
{
	mStart.X = iX;
	mStart.Y = iY;
}

void GtDrawMouseRectangle::SetEndPoint(int iX, int iY)
{
	mEnd.X = iX;
	mEnd.Y = iY;
}