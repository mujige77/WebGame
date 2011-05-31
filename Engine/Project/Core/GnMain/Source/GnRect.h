#ifndef GNRECT_H
#define GNRECT_H

template<typename T>
class GNMAIN_ENTRY GnRect : public GnMemoryObject
{
public:
	T left;
	T top;	
	T right;
	T bottom;
public:
	GnRect() : left(0), top(0), right(0), bottom(0)
	{}
	GnRect(T l, T t, T r, T b) : left(l), top(t), right(r), bottom(b)
	{}

	void MoveX(T val) {
		left += val;
		right += val;
	}
	void MoveY(T val) {
		top += val;
		bottom += val;
	}
	void SetWidth(T val) {
		T delta = val - GetWidth();
		right += delta;
	}
	void SetHeight(T val) {
		T delta = val - GetHeight();
		bottom += delta;
	}
	inline T GetWidth(){
		return right - left;
	};
	inline T GetHeight(){
		return bottom - top;
	};
};

class GNMAIN_ENTRY GnFRect : public GnRect<float>
{
	GnDeclareDataStream;
	GnFRect() {
	}
	GnFRect(float l, float t, float r, float b) : GnRect<float>(l, t, r, b){
	}
};

class GNMAIN_ENTRY GnIRect : public GnRect<gint32>
{
	GnDeclareDataStream;
	GnIRect() {
	}
	GnIRect(gint32 l, gint32 t, gint32 r, gint32 b) : GnRect<gint32>(l, t, r, b){
	}
};

#endif // GNRECT_H