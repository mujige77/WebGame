#ifndef GNSTREAMRTTIHELPER_H
#define GNSTREAMRTTIHELPER_H

#define GENIE_MAJOR_VERSION 1
#define GENIE_MINOR_VERSION 0
#define GENIE_PATCH_VERSION 0
#define GENIE_INTERNAL_VERSION 0


class GnObject;
class GnStream;
class GnObjectStream;
class GnStreamHelper;

#define GnDeclareDataStream \
	public: \
	typedef GnStream StreamType; \
	virtual void LoadStream(GnStream* pStream); \
	virtual void SaveStream(GnStream* pStream)

#define GnDeclareAbstractStream \
	public: \
	typedef GnObjectStream StreamType; \
	virtual void LoadStream(GnObjectStream* pStream); \
	virtual void SaveStream(GnObjectStream* pStream); \
	virtual void LinkObject(GnObjectStream* pStream); \
	virtual void RegisterSaveObject(GnObjectStream* pStream)
		

#define GnDeclareStream \
	GnDeclareAbstractStream; \
	static GnObject* CreateObject()

// macros for creating a object
#define GnImplementCreateObject(classname) \
	GnObject* classname::CreateObject() \
	{ \
		classname* object = GnNew classname; \
		GnAssert(object != NULL); \
		return object; \
	}

#define  GnRegisterStream(classname) \
	GnStreamHelper::RegisterRTTIObject(#classname, classname::CreateObject)

#ifdef GNDEBUG
#define  GnUnregisterStream(classname) \
	GnStreamHelper::UnRegisterRTTIObject(#classname)
#else
	#define  GnUnregisterStream(classname) GNNOOP
#endif // GNDEBUG
	


#endif // GNSTREAMRTTIHELPER_H