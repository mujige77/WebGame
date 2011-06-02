#pragma once
class GtDrawGDI
{
private:
	Pen mPen;	

public:
	GtDrawGDI(void);
	~GtDrawGDI(void);
	
	virtual void Draw(CDC *pDC,int nSx,int nSy,int iWidth, int iHeight);
	virtual void Draw(CDC *pDC, Gdiplus::Rect Rect);
	virtual void Draw(HDC pDC,int nSx,int nSy,int iWidth, int iHeight);
	virtual void Draw(HDC pDC, Gdiplus::Rect Rect);

	inline Pen* GetPen() {
		return &mPen;
	}
	inline COLORREF GetColor() {
		Color color;
		mPen.GetColor( &color );
		return color.GetValue();
	}
	inline void SetColor(COLORREF val) {
		mPen.SetColor( Color(val) );
	}
	inline float GetThick() {
		return mPen.GetWidth();
	}
	inline void SetThick(float val) {
		mPen.SetWidth( val );
	}

protected:
	virtual void DoDraw(Graphics& graphics,int iStartx,int iStarty,int iWidth, int iHeight) = 0;
};

