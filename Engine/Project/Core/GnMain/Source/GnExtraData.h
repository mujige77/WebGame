#ifndef GNEXTRADATA_H
#define GNEXTRADATA_H

class GnExtraData : public GnObject
{
	
	GnDeclareRTTI;
	GnDeclareAbstractStream;
public:
	static const guint32 NULL_TYPE = GUINT32_MAX;	
protected:
	guint32 mID;
	guint32 mType;

public:
	inline GnExtraData() : mType( NULL_TYPE ) {

	}
	inline guint32 GetID() {
		return mID;
	}
	inline void SetID(guint32 uiID) {
		mID = uiID;
	}
	inline gtuint GetType() {
		return mType;
	}
	inline void SetType(guint32 uiType) {
		mType = uiType;
	}
};

class GnIntExtraData : public GnExtraData
{
	GnDeclareRTTI;
	GnDeclareStream;
protected:
	gint32 mVal;

public:
	inline GnIntExtraData() : mVal( 0 ) {
	}
	inline gint32 GetValue() {
		return mVal;
	}
	inline void SetValue(gint32 uiVal) {
		mVal = uiVal;
	}
};

class GnVector2ExtraData : public GnExtraData
{
	GnDeclareRTTI;
	GnDeclareStream;
private:
	float mVector[2];

public:
	inline GnVector2ExtraData() {
		mVector[0] = mVector[1] = 0.0f;
	}
	inline GnVector2ExtraData(float* pfVector2) {
		SetValue( pfVector2 );
	}
	inline GnVector2ExtraData(GnVector2 cVector) {
		SetValue( cVector );
	}
	inline void SetValue(float* pfVector2) {
		mVector[0] = pfVector2[0];
		mVector[1] = pfVector2[1];
	}
	inline float* GetValue() {
		return mVector;
	}
	inline void SetValue(GnVector2 cVector) {
		mVector[0] = cVector.x;
		mVector[1] = cVector.y;
	}
	inline void SetValueX(float val) {
		mVector[0] = val;
	}
	inline void SetValueY(float val) {
		mVector[1] = val;
	}
	inline GnVector2 GetValueVector2() {
		return GnVector2( mVector[0], mVector[1] );
	}
};


#endif // GNEXTRADATA_H