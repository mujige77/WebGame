#ifndef GNRECT_H
#define GNRECT_H

class GNMAIN_ENTRY GnFRect : public GnMemoryObject
{
	GnDeclareDataStream;
public:
	float left;
	float top;	
	float right;
	float bottom;

public:
	GnFRect();
	GnFRect(float l, float t, float r, float b);
	virtual ~GnFRect(){};

	inline float GetWidth(){ return right - left; };
	inline float GetHeight(){ return bottom - top; };
};

class GNMAIN_ENTRY GnIRect : public GnMemoryObject
{
	GnDeclareDataStream;
public:
	gint32 left;
	gint32 top;	
	gint32 right;
	gint32 bottom;

public:
	GnIRect();
	GnIRect(gint32 l, gint32 t, gint32 r, gint32 b);
	virtual ~GnIRect(){};

	inline gint32 GetWidth(){ return right - left; };
	inline gint32 GetHeight(){ return bottom - top; };	
};
#endif // GNRECT_H