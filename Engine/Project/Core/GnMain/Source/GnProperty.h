#ifndef GNPROPERTY_H
#define GNPROPERTY_H

#include "GnObject.h"

class GnProperty : public GnObject
{
	GnDeclareRTTI;

protected:
	bool mIsSequenceProperty;
	
public:
	enum ePropertyType
	{
		TEXTURE_PROPERTY,
		PROPERTY_MAX,
	}; 

public:
	GnProperty();

	virtual ~GnProperty(){};

	// 현재 프로퍼티 타입을 설정
	virtual gtuint GetType() = 0;	

	inline bool IsControllerProperty() {
		return mIsSequenceProperty;
	}
	inline void SetTimeControllerProperty(bool val) {
		mIsSequenceProperty = val;
	}
};

GnSmartPointer(GnProperty);

#endif // GNPROPERTY_H