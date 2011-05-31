#ifndef GNTEGIDKEY_H
#define GNTEGIDKEY_H
#include "GnAnimationKey.h"

class GnTegIDKey : public GnAnimationKey
{
	GnDeclareAnimationStream;
protected:
	guint32 mTegID;

public:
	GnTegIDKey(){};
	virtual ~GnTegIDKey(){};

	inline guint32 GetTegID() {
		return mTegID;
	}
	inline void SetTegID(guint32 val) {
		mTegID = val;
	}
private:
};

GnRegsterAnimationKeyStream(GnTegIDKey);
#endif // GNTEGIDKEY_H