#ifndef GNTYPETRAITS_H
#define GNTYPETRAITS_H
//#include "GnList.h"
//template<> struct __TypeTraits<bool> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<char> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<signed char> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<unsigned char> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<wchar_t> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<short> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<unsigned short> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<int> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<unsigned int> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<long> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<unsigned long> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<long long> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<unsigned long long> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<float> : __type_traits_aux<1> {};
//template<> struct __TypeTraits<double> : __type_traits_aux<1> {};
namespace GnT
{
	// const 키워드 제거
	template <class U> struct UnConst
	{
		typedef U Result;
		enum { isConst = 0 };
	};
	template <class U> struct UnConst<const U>
	{
		typedef U Result;
		enum { isConst = 1 };
	};
	template <class U> struct UnConst<const U&>
	{
		typedef U& Result;
		enum { isConst = 1 };
	};

	// volatile 키워드 제거
	template <class U> struct UnVolatile
	{
		typedef U Result;
		enum { isVolatile = 0 };
	};
	template <class U> struct UnVolatile<volatile U>
	{
		typedef U Result;
		enum { isVolatile = 1 };
	};
	template <class U> struct UnVolatile<volatile U&>
	{
		typedef U& Result;
		enum { isVolatile = 1 };
	};

	template <class U> struct ReferenceTraits
	{
		enum { result = false };
		typedef U* PointeeType;
		typedef U ReferredType;
	};
	template <class U> struct ReferenceTraits< U& >
	{
		enum { result = true };
		typedef U* PointeeType;
		typedef U ReferredType;
	};

	template <class U> struct PointerTraits
	{
		enum { result = false };
		typedef _NullType PointeeType;

		inline static void SetNull(U& val)
		{
		}
	};
	template <class U> struct PointerTraits< U* >
	{
		enum { result = true };
		typedef U PointeeType;
		typedef U* ReferenceType;
		inline static void SetNull(U* val)
		{
			val = NULL;
		}
	};
	template <class U> struct PointerTraits< U*& >
	{
		enum { result = true };
		typedef U PointeeType;
		typedef U* ReferenceType;

		inline static void SetNull(U*& val)
		{
			val = NULL;
		}
	};
	template <class U> struct PointerTraits< GnPointer<U> >
	{
		enum { result = true };
		typedef U PointeeType;
		typedef U* ReferenceType;
		inline static void SetNull(GnPointer<U>& val)
		{
			val = NULL;
		}
	};
	template <class U> struct PointerTraits< GnPointer<U>& >
	{
		enum { result = true };
		typedef U PointeeType;
		typedef U* ReferenceType;

		inline static void SetNull( GnPointer<U>& val )
		{
			val = NULL;
		}
	};

	template <typename T>
	struct _TypeTraits
	{
		typedef typename UnConst<T>::Result 
			NonConstType;
		typedef typename UnVolatile<T>::Result 
			NonVolatileType;
		typedef typename UnVolatile<NonConstType>::Result 
			UnqualifiedType;
		typedef typename PointerTraits<UnqualifiedType>::PointeeType 
			PointeeType;
		typedef typename ReferenceTraits<T>::ReferredType 
			ReferredType;
	};

	template <int T> 
	struct TypeTraitsAux
	{
		typedef _FalseType    has_trivial_default_constructor;
		typedef _FalseType    has_trivial_copy_constructor;
		typedef _FalseType    has_trivial_assignment_operator;
		typedef _FalseType    has_trivial_destructor;
		typedef _FalseType    is_POD_type;
		enum { isTrue = _FalseType::isTrue };
	};

	template<> struct TypeTraitsAux<0>
	{
		typedef _FalseType    has_trivial_default_constructor;
		typedef _FalseType    has_trivial_copy_constructor;
		typedef _FalseType    has_trivial_assignment_operator;
		typedef _FalseType    has_trivial_destructor;
		typedef _FalseType    is_POD_type;
		enum { isTrue = _FalseType::isTrue };
	};

	template<> struct TypeTraitsAux<1>
	{ 
		typedef _TrueType    has_trivial_default_constructor;
		typedef _TrueType    has_trivial_copy_constructor;
		typedef _TrueType    has_trivial_assignment_operator;
		typedef _TrueType    has_trivial_destructor;
		typedef _TrueType    is_POD_type;
		enum { isTrue = _TrueType::isTrue };
	};

	template<typename T> struct TypeTraits : public TypeTraitsAux<0>
	{
		inline static bool TestMax(T&) {
			return true;
		}
	};
	template<> struct TypeTraits<bool> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(bool&) {
			return true;
		}
	};
	template<> struct TypeTraits<gchar> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(gchar& val) {
			if( GCHAR_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<gschar> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(gschar& val) {
			if( GSCHAR_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<guchar> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(guchar& val) {
			if( GUCHAR_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<gwchar> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(gwchar& val) {
			if( GWCHAR_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<gshort> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(gshort& val) {
			if( GSHORT_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<gushort> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(gushort& val) {
			if( GUSHORT_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<gint> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(gint& val) {
			if( GINT_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<guint> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(guint& val) {
			if( GUINT_MAX > val )
				return true;
			return false;
		}
	};
	//template<> struct TypeTraits<gint8> : TypeTraitsAux<1> {}; // signed char
	//template<> struct TypeTraits<guint8> : TypeTraitsAux<1> {}; // guchar
	//template<> struct TypeTraits<gint16> : TypeTraitsAux<1> {}; // gshort
	//template<> struct TypeTraits<guint16> : TypeTraitsAux<1> {}; // gushort
	//template<> struct TypeTraits<gint32> : TypeTraitsAux<1> {}; // gint
	//template<> struct TypeTraits<guint32> : TypeTraitsAux<1> {}; // guint
	template<> struct TypeTraits<gint64> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(gint64& val) {
			if( GINT64_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<guint64> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(guint64& val) {
			if( GUINT64_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<glong> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(glong& val) {
			if( GLONG_MAX > val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<gulong> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(gulong& val) {
			if( GULONG_MAX >= val )
				return true;
			return false;
		}
	};
	template<> struct TypeTraits<float> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(float& val) {
			return true;
		}
	};
	template<> struct TypeTraits<double> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(double& val) {
			return true;
		}
	};
	template<> struct TypeTraits<long double> : public TypeTraitsAux<1>
	{
		inline static bool TestMax(long double& val) {
				return true;
		}
	};

	//template <class U> struct PointerTraits<GnList<U>*>
	//{
	//	enum { result = true };
	//	typedef U PointeeType;
	//	typedef U* ReferenceType;
	//	inline static void SetNull(GnList<U>* val)
	//	{
	//		val = NULL;
	//	}
	//};

	//template <class U> struct PointerTraits<GnList<U>*&>
	//{
	//	enum { result = true };
	//	typedef U PointeeType;
	//	typedef U* ReferenceType;

	//	inline static void SetNull(GnList<U>* val)
	//	{
	//		val = NULL;
	//	}
	//};
}
#endif // GNTYPETRAITS_H