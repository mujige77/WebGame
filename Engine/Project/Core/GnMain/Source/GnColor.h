#ifndef GNCOLOR_H
#define GNCOLOR_H

#include <GnMemoryObject.h>


class GNMAIN_ENTRY GnColorA : public GnMemoryObject
{
public:
	float r, g, b, a;

	inline GnColorA (float fR = 0.0f, float fG = 0.0f, 
		float fB = 0.0f, float fA = 1.0f);

	inline GnColorA& operator= (float fScalar);
	inline bool operator== (const GnColorA& c) const;
	inline bool operator!= (const GnColorA& c) const;

	inline GnColorA operator+ (const GnColorA& c) const;
	inline GnColorA operator- (const GnColorA& c) const;
	inline GnColorA operator* (float fScalar) const;
	inline GnColorA operator* (const GnColorA& c) const;
	inline GnColorA operator/ (float fScalar) const;
	inline GnColorA operator/ (const GnColorA& c) const;
	inline GnColorA operator- () const;
	GNMAIN_ENTRY friend GnColorA operator* (float fScalar, const GnColorA& c);

	inline GnColorA& operator+= (const GnColorA& c);
	inline GnColorA& operator-= (const GnColorA& c);
	inline GnColorA& operator*= (float fScalar);
	inline GnColorA& operator*= (const GnColorA& c);
	inline GnColorA& operator/= (float fScalar);
	inline GnColorA& operator/= (const GnColorA& c);

	// map (r,g,b,a) to unit hypercube
	inline void Clamp();
	inline void Scale();

	// Function to return the color as an unsigned integer.
	inline guint32 GetRGBA() const;
	inline void GetRGBA(guint8& outR, guint8& outG, guint8& outB, guint8& outA);
};

inline GnColorA::GnColorA(float fR, float fG, float fB, float fA)
{
	r = fR;
	g = fG;
	b = fB;
	a = fA;
}

inline GnColorA& GnColorA::operator= (float fScalar)
{
	r = fScalar;
	g = fScalar;
	b = fScalar;
	a = fScalar;
	return *this;
}

inline bool GnColorA::operator== (const GnColorA& c) const
{
	return (r == c.r && g == c.g && b == c.b && a == c.a);
}

inline bool GnColorA::operator!= (const GnColorA& c) const
{
	return !(*this == c);
}

inline GnColorA GnColorA::operator+ (const GnColorA& c) const
{
	GnColorA result = *this;
	result.r += c.r;
	result.g += c.g;
	result.b += c.b;
	result.a += c.a;
	return result;
}

inline GnColorA GnColorA::operator- (const GnColorA& c) const
{
	GnColorA result = *this;
	result.r -= c.r;
	result.g -= c.g;
	result.b -= c.b;
	result.a -= c.a;
	return result;
}

inline GnColorA GnColorA::operator* (float fScalar) const
{
	GnColorA result = *this;
	result.r *= fScalar;
	result.g *= fScalar;
	result.b *= fScalar;
	result.a *= fScalar;
	return result;
}

inline GnColorA GnColorA::operator* (const GnColorA &c) const
{
	GnColorA result = *this;
	result.r *= c.r;
	result.g *= c.g;
	result.b *= c.b;
	result.a *= c.a;
	return result;
}

inline GnColorA GnColorA::operator/ (float fScalar) const
{
	GnColorA result = *this;
	result.r /= fScalar;
	result.g /= fScalar;
	result.b /= fScalar;
	result.a /= fScalar;
	return result;
}

inline GnColorA GnColorA::operator/ (const GnColorA &c) const
{
	GnColorA result = *this;
	result.r /= c.r;
	result.g /= c.g;
	result.b /= c.b;
	result.a /= c.a;
	return result;
}

inline GnColorA GnColorA::operator- () const
{
	return GnColorA(-r,-g,-b,-a);
}

inline GnColorA operator* (float fScalar, const GnColorA& c)
{
	return c*fScalar;
}

inline GnColorA& GnColorA::operator+= (const GnColorA& c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	a += c.a;
	return *this;
}

inline GnColorA& GnColorA::operator-= (const GnColorA& c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;
	a -= c.a;
	return *this;
}

inline GnColorA& GnColorA::operator*= (float fScalar)
{
	r *= fScalar;
	g *= fScalar;
	b *= fScalar;
	a *= fScalar;
	return *this;
}

inline GnColorA& GnColorA::operator*= (const GnColorA &c)
{
	r *= c.r;
	g *= c.g;
	b *= c.b;
	a *= c.a;
	return *this;
}

inline GnColorA& GnColorA::operator/= (float fScalar)
{
	r /= fScalar;
	g /= fScalar;
	b /= fScalar;
	a /= fScalar;
	return *this;
}

inline GnColorA& GnColorA::operator/= (const GnColorA &c)
{
	r /= c.r;
	g /= c.g;
	b /= c.b;
	a /= c.a;
	return *this;
}

inline void GnColorA::Clamp()
{
	// Clamp to [0,1]^4.  Assumes that (r,g,b,a) >= (0,0,0).  This is a
	// reasonable assumption since colors are only added or multiplied in
	// the lighting system.  Note that clamping can cause significant
	// changes in the final color.
	if ( r > 1.0f )
		r = 1.0f;
	if ( g > 1.0f )
		g = 1.0f;
	if ( b > 1.0f )
		b = 1.0f;
	if ( a > 1.0f )
		a = 1.0f;
}

inline void GnColorA::Scale()
{
	// Scale down by maximum component (preserves the final color).
	float fMax = r;
	if ( g > fMax )
		fMax = g;
	if ( b > fMax )
		fMax = b;

	if ( fMax > 1.0f )
	{
		float fInvMax = 1.0f/fMax;
		r *= fInvMax;
		g *= fInvMax;
		b *= fInvMax;
	}

	if ( a > 1.0f )
		a = 1.0f;
}

inline guint32 GnColorA::GetRGBA() const
{
	return ((int)(a * 255.0f) << 24 ) | ((int)(r * 255.0f) << 16) | ((int)(g * 255.0f) << 8 ) | (int)(b * 255.0f);
}

inline void GnColorA::GetRGBA(guint8& outR, guint8& outG, guint8& outB, guint8& outA)
{
	outR = (int)(r * 255.0f);
	outG = (int)(g * 255.0f);
	outB = (int)(b * 255.0f);
	outA = (int)(a * 255.0f);
}

#endif // GNCOLOR_H