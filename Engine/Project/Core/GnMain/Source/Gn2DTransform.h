#ifndef GN2DTRANSFORM_H
#define GN2DTRANSFORM_H

#include "GnTransform.h"

class GNMAIN_ENTRY Gn2DTransform : public GnTransform
{
protected:
	GnVector3 mPostion;	
	GnVector2 mScale;	
	float mRotAngle;

public:
	Gn2DTransform(){};
	virtual ~Gn2DTransform(){};

public:
	inline GnVector3& GetPostion() { return mPostion; }
	inline void SetPostion(GnVector3 val) { mPostion = val; }
	inline GnVector2& GetScale() { return mScale; }
	inline void SetScale(GnVector2 val) { mScale = val; }
	inline float GetRotAngle() const { return mRotAngle; }
	inline void SetRotAngle(float val) { mRotAngle = val; }

protected:
	
private:
};

#endif // GN2DTRANSFORM_H