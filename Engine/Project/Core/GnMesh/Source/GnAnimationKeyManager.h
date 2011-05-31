#ifndef GNANIMATIONKEYMANAGER_H
#define GNANIMATIONKEYMANAGER_H
#include "GnAnimationKey.h"

class GnAnimationKeyManager : public GnMemoryObject
{
	GnDeclareDataStream;
public:
	class AniKey
	{
	public:
		AniKey();
		GnAnimationKey::eKeyType mKeyType;
		guint32 mNumKey;
		GnAnimationKey* mAnimationKeys;
	};

private:
	GnTPrimitiveArray<AniKey> mAnimationKeys;

public:
	GnAnimationKeyManager(){};
	virtual ~GnAnimationKeyManager();



	// 툴 때문에 만든 것임
public:
	inline GnTPrimitiveArray<AniKey>* GetAnimationKeys() {
		return &mAnimationKeys;
	}
};

#endif // GNANIMATIONKEYMANAGER_H