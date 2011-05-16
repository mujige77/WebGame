#ifndef GNRTTI_H
#define GNRTTI_H

class GNMAIN_ENTRY GnRTTI
{
public:
	GnRTTI( const gchar* pName, const GnRTTI* pBaseRTTI );

	const gchar* GetName() const { return mpName; }
	const GnRTTI* GetBaseRTTI() const { return mpBaseRTTI; }

	bool CopyName( gchar* nameBuffer, gtuint uiMaxSize ) const;

protected:
	const gchar* mpName;
	const GnRTTI* mpBaseRTTI;
};

// insert in root class declaration
#define GnDeclareRootRTTI(classname) \
	public: \
		static const GnRTTI msRTTI; \
		virtual const GnRTTI* GetRTTI() const {return &msRTTI;} \
		static bool IsExactKindOf(const GnRTTI* pRTTI, const classname* pObject) \
		{ \
			if (!pObject) \
		{ \
			return false; \
		} \
			return pObject->IsExactKindOf(pRTTI); \
		} \
		bool IsExactKindOf(const GnRTTI* pRTTI) const \
		{ \
			return (GetRTTI() == pRTTI); \
		} \
		static bool IsKindOf(const GnRTTI* pRTTI, \
		const classname* pObject) \
		{ \
			if (!pObject) \
				return false; \
			return pObject->IsKindOf(pRTTI); \
		} \
		bool IsKindOf(const GnRTTI* pRTTI) const \
		{ \
			const GnRTTI* pTmp = GetRTTI(); \
			while (pTmp) \
			{ \
				if (pTmp == pRTTI) \
					return true; \
				pTmp = pTmp->GetBaseRTTI(); \
			} \
			return false; \
		} \
		static classname* VerifyStaticCastDebug(const GnRTTI* pRTTI, const classname* pObject) \
		{ \
			if (!pObject) \
			{ \
				return NULL; \
			} \
			classname* pDynamicCast = DynamicCast(pRTTI, pObject); \
			GnAssert("NiVerifyStaticCast() caught an invalid type cast." \
			"Check callstack for invalid object typecast assumption." && pDynamicCast); \
			return pDynamicCast; \
		} \
		static classname* DynamicCast(const GnRTTI* pRTTI, const classname* pObject) \
		{ \
			if (!pObject) \
				return NULL; \
			return pObject->DynamicCast(pRTTI); \
		} \
		classname* DynamicCast(const GnRTTI* pRTTI) const \
		{ \
			return (IsKindOf(pRTTI) ? (classname*) this : 0 ); \
		}

// insert in class declaration
#define GnDeclareRTTI \
	public: \
		static const GnRTTI msRTTI; \
		virtual const GnRTTI* GetRTTI() const {return &msRTTI;}

// insert in root class source file
#define GnImplementRootRTTI(rootclassname) \
	const GnRTTI rootclassname::msRTTI(#rootclassname, 0)

// insert in class source file
#define GnImplementRTTI(classname, baseclassname) \
	const GnRTTI classname::msRTTI(#classname, &baseclassname::msRTTI)

// macros for run-time type testing
#define GnIsExactKindOf(classname, pObject) \
	classname::IsExactKindOf(&classname::msRTTI, pObject)

#define GnIsKindOf(classname, pObject) \
	classname::IsKindOf(&classname::msRTTI, pObject)

// macro for compile time type casting
#define GnStaticCast(classname, pObject) ((classname*) pObject)

// macro for compile time type casting, with debug run-time assert
#ifdef GNDEBUG
	#define GnVerifyStaticCast(classname, pObject) \
		((classname*) classname::VerifyStaticCastDebug( &classname::msRTTI, pObject))
#else
	#define GnVerifyStaticCast(classname, pObject) ((classname*) (pObject))
#endif

// macro for run-time type casting, returns NULL if invalid cast
#define GnDynamicCast(classname, pObject) \
	((classname*) classname::DynamicCast(&classname::msRTTI, pObject))

#endif // GNRTTI_H
