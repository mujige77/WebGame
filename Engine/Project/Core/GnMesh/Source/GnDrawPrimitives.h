#ifndef GNDRAWPRIMITIVES_H
#define GNDRAWPRIMITIVES_H

class GnDrawPrimitives : public GnSmartObject
{
protected:
	GnColorA mColor;
	float mThickness;
	
public:
	GnDrawPrimitives();
	virtual ~GnDrawPrimitives();

	virtual void Draw() = 0;

	inline float GetThickness() {
		return mThickness;
	}
	inline void SetThickness(float val) {
		mThickness = val;
	}
	inline GnColorA& GetColor() {
		return mColor;
	}
	inline void SetColor(GnColorA val) {
		mColor = val;
	}

protected:
	void DrawRect(GnIRect iRect);
	void DrawRect(GnFRect fRect);
	void DrawRect(float fLeft, float fTop, float fRight, float fBottom);
	void DrawPoint(GnVector2 vPoint);
};
GnSmartPointer(GnDrawPrimitives);

class GnDrawRect : public GnDrawPrimitives
{
protected:
	GnFRect mRect;

public:
	virtual void Draw();
};

class GnDraw2DObjectRect : public GnDrawPrimitives
{
	GnDeclareFlags(gushort);
public:
	enum eSMFlag
	{
		MASK_DRAWANCHORPINT = 0x0001,
		MASK_CONVERTCOCOSRECT = 0x0002,
	};

protected:
	Gn2DAVData mBaseAVData;
	GnTObjectArray<GnDrawPrimitivesPtr> mDraws;

protected:
	Gn2DMeshObjectPtr mpObject;

public:
	GnDraw2DObjectRect();
	virtual ~GnDraw2DObjectRect(){};

	virtual void Draw();

	inline bool IsDrawAnchorPoint() {
		return GetBit( MASK_DRAWANCHORPINT );
	}
	inline void SetDrawAnchorPoint(bool val) {
		SetBit( val, MASK_DRAWANCHORPINT );
	}
	inline bool IsConvertCocosRect() {
		return GetBit( MASK_CONVERTCOCOSRECT );
	}
	inline void SetConvertCocosRect(bool val) {
		SetBit( val, MASK_CONVERTCOCOSRECT);
	}

	inline Gn2DMeshObjectPtr GetObject() {
		return mpObject;
	}
	inline void SetObject(Gn2DMeshObjectPtr val) {
		mpObject = val;
	}
};

#endif // GNDRAWPRIMITIVES_H