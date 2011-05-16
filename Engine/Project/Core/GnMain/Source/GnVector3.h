#ifndef GNVECTOR3_H
#define GNVECTOR3_H
#include <GnMemoryObject.h>


class GNMAIN_ENTRY GnVector3 : public GnMemoryObject
{
public:
	GnVector3() {};
	GnVector3( const float * );
	GnVector3( const GnVector3& );	
	GnVector3( float x, float y, float z );

	// casting
	operator float* ();
	operator const float* () const;

	// assignment operators
	GnVector3& operator += ( const GnVector3& );
	GnVector3& operator -= ( const GnVector3& );
	GnVector3& operator *= ( float );
	GnVector3& operator /= ( float );

	// unary operators
	GnVector3 operator + () const;
	GnVector3 operator - () const;

	// binary operators
	GnVector3 operator + ( const GnVector3& ) const;
	GnVector3 operator - ( const GnVector3& ) const;
	GnVector3 operator * ( float ) const;
	GnVector3 operator / ( float ) const;

	friend GnVector3 operator * ( float, const class GnVector3& );

	bool operator == ( const GnVector3& ) const;
	bool operator != ( const GnVector3& ) const;

	float x;
	float y;
	float z;

};

inline GnVector3::GnVector3( const float *pf )
{
#ifdef GNDEBUG
	if(!pf)
		return;
#endif

	x = pf[0];
	y = pf[1];
	z = pf[2];
}

inline GnVector3::GnVector3( const GnVector3& v )
{
	x = v.x;
	y = v.y;
	z = v.z;
}

inline GnVector3::GnVector3( float fx, float fy, float fz )
{
	x = fx;
	y = fy;
	z = fz;
}


// casting
inline GnVector3::operator float* ()
{
	return (float *) &x;
}

inline GnVector3::operator const float* () const
{
	return (const float *) &x;
}


// assignment operators
inline GnVector3& GnVector3::operator += ( const GnVector3& v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline GnVector3& GnVector3::operator -= ( const GnVector3& v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline GnVector3& GnVector3::operator *= ( float f )
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

inline GnVector3& GnVector3::operator /= ( float f )
{
	float fInv = 1.0f / f;
	x *= fInv;
	y *= fInv;
	z *= fInv;
	return *this;
}


// unary operators
inline GnVector3 GnVector3::operator + () const
{
	return *this;
}

inline GnVector3 GnVector3::operator - () const
{
	return GnVector3(-x, -y, -z);
}


// binary operators
inline GnVector3 GnVector3::operator + ( const GnVector3& v ) const
{
	return GnVector3(x + v.x, y + v.y, z + v.z);
}

inline GnVector3 GnVector3::operator - ( const GnVector3& v ) const
{
	return GnVector3(x - v.x, y - v.y, z - v.z);
}

inline GnVector3 GnVector3::operator * ( float f ) const
{
	return GnVector3(x * f, y * f, z * f);
}

inline GnVector3 GnVector3::operator / ( float f ) const
{
	float fInv = 1.0f / f;
	return GnVector3(x * fInv, y * fInv, z * fInv);
}


inline GnVector3 operator * ( float f, const class GnVector3& v )
{
	return GnVector3(f * v.x, f * v.y, f * v.z);
}


inline bool GnVector3::operator == ( const GnVector3& v ) const
{
	return x == v.x && y == v.y && z == v.z;
}

inline bool GnVector3::operator != ( const GnVector3& v ) const
{
	return x != v.x || y != v.y || z != v.z;
}

#endif // GNVECTOR3_H