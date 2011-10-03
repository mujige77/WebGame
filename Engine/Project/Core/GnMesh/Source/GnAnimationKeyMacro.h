#ifndef GNANIMATIONKEYMACRO_H
#define GNANIMATIONKEYMACRO_H

class GnStream;
class GnAnimationKey;
#define GnDeclareRootAnimationStream \
public: \
	typedef GnStream StreamType; \
	static int RegisterStream(); \
	virtual void LoadStream(GnStream* pStream); \
	virtual void SaveStream(GnStream* pStream); \
protected: \
	static GnAnimationKey* LoadFromStream(GnStream* pStream, guint32 numKey ); \
	static void SaveToStream(GnStream* pStream, guint32 numKey, GnAnimationKey* pKeys)

#define GnDeclareAnimationStream \
GnDeclareRootAnimationStream; \
public: \
	static GnAnimationKey* GetKey(GnAnimationKey* pAnimations, guint32 uiIndex); \
	static void Destroy(GnAnimationKey* pKeys); \

#define GnRegsterAnimationKeyStream(classname) \
	static int classname##RegsterAnimationKeyReturn = classname::RegisterStream()

#define GnImplementCreateAnimationKey(classname, type) \
	int classname::RegisterStream() \
	{ \
		static bool bRegistered = false; \
		if(bRegistered) \
			return 0; \
		RegLoadFunction(type, classname::LoadFromStream); \
		RegSaveFunction(type, classname::SaveToStream); \
		RegDestroyFunction(type, classname::Destroy); \
		RegGetKeyAnimationFunction(type, classname::GetKey); \
		return 1; \
	} \
	void classname::Destroy(GnAnimationKey* pKeys) \
	{ \
		classname* thisKey = (classname*)pKeys; \
		GnDelete[] thisKey; \
	} \
	GnAnimationKey* classname::GetKey(GnAnimationKey* pAnimations, guint32 uiIndex) \
	{ \
		classname* aniKey = (classname*)pAnimations; \
		return &aniKey[uiIndex]; \
	} 
#endif // GNANIMATIONKEYMACRO_H