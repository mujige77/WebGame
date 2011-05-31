#ifndef GNSTREAM_H
#define GNSTREAM_H
#include <GnTStringMap.h>

class GNMAIN_ENTRY GnStreamHelper : public GnMemoryObject
{	
public:
	typedef GnObject* (*LoadFunction)();

protected:
	static GnTStringMap<LoadFunction>* mCreateFunctions;
	LoadFunction mCreateFunction;

public:
	static void EBMStartup();
	static void EBMShutdown();
	static void RegisterRTTIObject(gchar* pcName, LoadFunction pFunc);
	static void UnRegisterRTTIObject(gchar* pcName);

	inline GnStreamHelper() : mCreateFunction(NULL) {
	}

	void SetRTTICreateFunction(gchar* pcName);

	inline GnObject* CreateObject()
	{
		return mCreateFunction();
	}
};

class GnStream : public GnMemoryObject
{
public:
	static const gtuint MAX_RTTINAME = 128;
	static const guint32 msGenieVersion;

protected:
	guint32 mFileVersion;
	GnFile* mpFile;

public:
	GnStream();
	virtual ~GnStream();

	virtual bool Load(const gchar* pcFilePath);
	virtual bool Save(const gchar* pcFilePath);

	inline void Close() {
		if( mpFile )
		{
			GnDelete mpFile;
			mpFile = NULL;
		}
	}

	template<class T>
	inline void SaveStream(T& val) {
		PointerTraits<T>::SaveBinary(this, val);
	}
	template<class T>
	inline void LoadStream(T& val) {
		PointerTraits<T>::LoadBinary(this, val);
	}
	template<class T>
	inline void SaveStream(T* val) {
		PointerTraits<T*>::SaveBinary(this, val);
	}
	template<class T>
	inline void LoadStream(T*& val) {
		PointerTraits<T*>::LoadBinary(this, val);
	}
	inline void SaveStreams(gchar* pcStr, gsize uiSize) {
		mpFile->SaveBinary( pcStr, uiSize );
	}
	inline void LoadStreams(gchar* pcStr, gsize uiSize) {
		mpFile->LoadBinary( pcStr, uiSize );
	}
	template <class U> struct PointerTraits
	{
		inline static void SaveBinary(GnStream* pStream, U& val) {
			GnAssert( GnT::TypeTraits< GnT::_TypeTraits<U>::UnqualifiedType >::TestMax( (GnT::_TypeTraits<U>::UnqualifiedType)val ) ); 
			pStream->CheckSave( val, 
				GnT::TypeTraits< GnT::_TypeTraits<U>::UnqualifiedType >::has_trivial_copy_constructor() );
		}
		inline static void LoadBinary(GnStream* pStream, U& val) {
			GnAssert( GnT::TypeTraits< GnT::_TypeTraits<U>::UnqualifiedType >::TestMax( (GnT::_TypeTraits<U>::UnqualifiedType)val ) );
			pStream->CheckLoad( val,
				GnT::TypeTraits< GnT::_TypeTraits<U>::UnqualifiedType >::has_trivial_copy_constructor() );
		}
	};

	template <class U> struct PointerTraits< U* >
	{
		inline static void SaveBinary(GnStream* pStream, U* val) {
			pStream->CheckSave( val, 
				GnT::TypeTraits< GnT::_TypeTraits<U>::UnqualifiedType >::has_trivial_copy_constructor() );
		}
		inline static void LoadBinary(GnStream*  pStream, U*& val) {
			pStream->CheckLoad( val,
				GnT::TypeTraits< GnT::_TypeTraits<U>::UnqualifiedType >::has_trivial_copy_constructor() );
		}
	};

	inline guint32 GetFileVersion() {
		return mFileVersion;
	}

	inline void SetFileVersion(guint32 uiMajor, guint32 uiMinor, guint32 uiPatch, guint32 uiInternal) {
		mFileVersion = (uiMajor << 24) | (uiMinor << 16) | (uiPatch << 8) | uiInternal;;
	}

	inline static guint32 GetVersion(guint32 uiMajor, guint32 uiMinor, guint32 uiPatch, guint32 uiInternal) {
		return (uiMajor << 24) | (uiMinor << 16) | (uiPatch << 8) | uiInternal;
	}

	inline gsize GetStringLengthSize() {
		return sizeof( gushort );
	}

protected:
	template<class T>
	inline void CheckLoad(T*& val, GnT::_FalseType) {
		val->LoadStream((T::StreamType*) this);
	}
	template<class T>
	inline void CheckSave(T* val, GnT::_FalseType) {
		val->SaveStream((T::StreamType*)this);
	}
	template<class T>
	inline void CheckLoad(T*& val, GnT::_TrueType) {
		LoadBinary( val );
	}
	template<class T>
	inline void CheckSave(T* val, GnT::_TrueType) {
		SaveBinary( val );
	}
	template<class T>
	inline void CheckLoad(T&val, GnT::_TrueType) {
		mpFile->LoadBinary( &val, sizeof(T) );
	}	
	template<class T>
	inline void CheckSave(T&val, GnT::_TrueType) {
		mpFile->SaveBinary( &val, sizeof(T) );
	}	
	void LoadBinary(gwchar*& val);
	void SaveBinary(const gwchar* val);
	void LoadBinary(gchar*& val);
	void SaveBinary(const gchar* val);
};

//GnAssert( GnT::TypeTraits< GnT::_TypeTraits<U>::UnqualifiedType >::isTrue );
#endif // GNSTREAM_H