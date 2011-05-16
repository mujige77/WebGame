#ifndef GNVECTOR2_H
#define GNVECTOR2_H
#include <GnMemoryObject.h>

class GNMAIN_ENTRY GnVector2 : public GnMemoryObject
{
public:
	inline GnVector2();
	inline GnVector2( const float * );
	inline GnVector2( float x, float y );

	// casting
	inline operator float* ();
	inline operator const float* () const;

	// assignment operators
	inline GnVector2& operator += ( const GnVector2& );
	inline GnVector2& operator -= ( const GnVector2& );
	inline GnVector2& operator *= ( float );
	inline GnVector2& operator /= ( float );

	// unary operators
	inline GnVector2 operator + () const;
	inline GnVector2 operator - () const;

	// binary operators
	inline GnVector2 operator + ( const GnVector2& ) const;
	inline GnVector2 operator - ( const GnVector2& ) const;
	inline GnVector2 operator * ( float ) const;
	inline GnVector2 operator / ( float ) const;

	friend GnVector2 operator * ( float, const GnVector2& );

	inline bool operator == ( const GnVector2& ) const;
	inline bool operator != ( const GnVector2& ) const;


public:
	float x, y;
};

inline GnVector2::GnVector2()
{
	GnVector2(0.0f, 0.0f);
}

inline GnVector2::GnVector2( const float *pf )
{
#ifdef GNDEBUG
	if(!pf)
		return;
#endif

	x = pf[0];
	y = pf[1];
}


inline GnVector2::GnVector2( float fx, float fy )
{
	x = fx;
	y = fy;
}


// casting

inline GnVector2::operator float* ()
{
	return (float *) &x;
}


inline GnVector2::operator const float* () const
{
	return (const float *) &x;
}


// assignment operators
inline GnVector2& GnVector2::operator += ( const GnVector2& v )
{
	x += v.x;
	y += v.y;
	return *this;
}

inline GnVector2& GnVector2::operator -= ( const GnVector2& v )
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline GnVector2&	GnVector2::operator *= ( float f )
{
	x *= f;
	y *= f;
	return *this;
}

inline GnVector2& GnVector2::operator /= ( float f )
{
	float fInv = 1.0f / f;
	x *= fInv;
	y *= fInv;
	return *this;
}


// unary operators
inline GnVector2 GnVector2::operator + () const
{
	return *this;
}

inline GnVector2 GnVector2::operator - () const
{
	return GnVector2(-x, -y);
}


// binary operators
inline GnVector2 GnVector2::operator + ( const GnVector2& v ) const
{
	return GnVector2(x + v.x, y + v.y);
}

inline GnVector2 GnVector2::operator - ( const GnVector2& v ) const
{
	return GnVector2(x - v.x, y - v.y);
}

inline GnVector2 GnVector2::operator * ( float f ) const
{
	return GnVector2(x * f, y * f);
}

inline GnVector2 GnVector2::operator / ( float f ) const
{
	float fInv = 1.0f / f;
	return GnVector2(x * fInv, y * fInv);
}

inline GnVector2	operator * ( float f, const GnVector2& v )
{
	return GnVector2(f * v.x, f * v.y);
}

inline bool GnVector2::operator == ( const GnVector2& v ) const
{
	return x == v.x && y == v.y;
}

inline bool GnVector2::operator != ( const GnVector2& v ) const
{
	return x != v.x || y != v.y;
}

#endif // GNVECTOR2_H