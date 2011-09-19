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
	
	inline bool ContainsPoint(T x, T y) {
		if (x >= left && x <= right && y >= top && y <= bottom )
			return true;
		return false;
	}
	inline bool ContainsPointX(T x) {
		if (x >= left && x <= right )
			return true;
		return false;
	}
	inline bool ContainsPointY(T y) {
		if ( y >= top && y <= bottom )
			return true;
		return false;
	}
	inline bool ContainsRect(GnRect<T>& rect) {
		if ( ( ( rect.left >= left && rect.left <= right ) || ( rect.right >= left && rect.right <= right ) )
			&& ( ( rect.top <= top && rect.top >= bottom ) || ( rect.bottom <= top && rect.bottom >= bottom ) ) )
			return true;
		return false;
	}
	inline bool ContainsRectHeight(GnRect<T>& rect) {
		if( ( rect.top >= top && rect.top <= bottom ) || ( rect.bottom >= top && rect.bottom <= bottom ) )
			return true;
		return false;
	}
	inline bool ContainsRectWidth(GnRect<T>& rect) {
		if ( ( rect.left >= left && rect.left <= right ) 
			|| ( rect.right >= left && rect.right <= right ) )
			return true;
		return false;
	}
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