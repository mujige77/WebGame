#ifndef GNANIMATIONKEYMACRO_H
#define GNANIMATIONKEYMACRO_H

class GnStream;
class GnAnimationKey;
#define GnDeclareAnimationStream \
public: \
	typedef GnStream StreamType; \
	static int RegisterStream(); \
	virtual void LoadStream(GnStream* pStream); \
	virtual void SaveStream(GnStream* pStream); \
protected: \
	static GnAnimationKey* LoadFromStream(GnStream* pStream, guint32 numKey ); \
	static void SaveToStream(GnStream* pStream, guint32 numKey, GnAnimationKey* pKeys )

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
		return 1; \
	}

#endif // GNANIMATIONKEYMACRO_H