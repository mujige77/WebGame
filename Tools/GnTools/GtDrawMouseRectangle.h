#pragma once
#include "GtDrawRect.h"

class GtDrawMouseRectangle : public GtDrawRect
{
protected:
	Rect mDrawRect;
	Point mStart;
	Point mEnd;
	bool mDraw;

public:
	GtDrawMouseRectangle(void);
	~GtDrawMouseRectangle(void);

	void Draw(CDC *pDC);

	void SetStartPoint(int iX, int iY);
	void SetEndPoint(int iX, int iY);	

	inline bool GetDraw() {
		return mDraw;
	}
	inline void SetDraw(bool val) {
		mDraw = val;
	}

	inline Rect GetDrawRect() {
		return mDrawRect;
	}
	inline void SetDrawRect(Rect val) {
		mDrawRect = val;
	}
	inline Point& GetEndPoint() {
		return mEnd;
	}
	inline void SetEndPoint(Point& val) {
		mEnd = val;
	}
	inline Point& GetStartPoint() {
		return mStart;
	}
	inline void SetStartPoint(Point& val) {
		mStart = val;
	}
};

