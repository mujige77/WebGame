#ifndef GNANIMATIONKEY_H
#define GNANIMATIONKEY_H
#include "GnAnimationKeyMacro.h"




class GnAnimationKey : public GnMemoryObject
{
	GnDeclareAnimationStream;
public:

	enum eKeyType
	{
		TEGIDKEY,
		MAX_KEYTYPE
	};


	typedef GnAnimationKey* (*LoadFunction)(GnStream*, guint32);	
	typedef void (*SaveFunction)(GnStream*, guint32, GnAnimationKey* save);

protected:
	float mKeyTime;

private:
	static LoadFunction msLoadFunction[MAX_KEYTYPE];
	static SaveFunction msSaveFunction[MAX_KEYTYPE];

public:
	GnAnimationKey() : mKeyTime(0.0f) {
	};
	virtual ~GnAnimationKey(){};	

	static LoadFunction GetLoadFunction(eKeyType eType);
	static SaveFunction GetSaveFunction(eKeyType eType);

	inline float GetKeyTime() {
		return mKeyTime;
	}
	inline void SetKeyTime(float val) {
		mKeyTime = val;
	}

protected:
	static void RegLoadFunction(eKeyType eType, LoadFunction funcCreate);
	static void RegSaveFunction(eKeyType eType, SaveFunction funcCreate);
};

#endif // GNANIMATIONKEY_H