#ifndef GNTYPEMANIP_H
#define GNTYPEMANIP_H

// $Id: TypeManip.h 749 2006-10-17 19:49:26Z syntheticpp $


namespace GnT
{
	////////////////////////////////////////////////////////////////////////////////
	// class template Int2Type
	// Converts each integral constant into a unique type
	// Invocation: Int2Type<v> where v is a compile-time constant integral
	// Defines 'value', an enum that evaluates to v
	////////////////////////////////////////////////////////////////////////////////

	template <int v>
	struct Int2Type
	{
		enum { value = v };
	};

	////////////////////////////////////////////////////////////////////////////////
	// class template Type2Type
	// Converts each type into a unique, insipid type
	// Invocation Type2Type<T> where T is a type
	// Defines the type OriginalType which maps back to T
	////////////////////////////////////////////////////////////////////////////////

	template <typename T>
	struct Type2Type
	{
		typedef T OriginalType;
	};

	////////////////////////////////////////////////////////////////////////////////
	// class template Select
	// Selects one of two types based upon a boolean constant
	// Invocation: Select<flag, T, U>::Result
	// where:
	// flag is a compile-time boolean constant
	// T and U are types
	// Result evaluates to T if flag is true, and to U otherwise.
	////////////////////////////////////////////////////////////////////////////////

	template <bool flag, typename T, typename U>
	struct Select
	{
		typedef T Result;
	};
	template <typename T, typename U>
	struct Select<false, T, U>
	{
		typedef U Result;
	};

	////////////////////////////////////////////////////////////////////////////////
	// class template IsSameType
	// Return true iff two given types are the same
	// Invocation: SameType<T, U>::value
	// where:
	// T and U are types
	// Result evaluates to true iff U == T (types equal)
	////////////////////////////////////////////////////////////////////////////////

	template <typename T, typename U>
	struct IsSameType
	{
		enum { value = false };
	};

	template <typename T>
	struct IsSameType<T,T>
	{
		enum { value = true };
	};

	////////////////////////////////////////////////////////////////////////////////
	// Helper types Small and Big - guarantee that sizeof(Small) < sizeof(Big)
	////////////////////////////////////////////////////////////////////////////////

	namespace Private
	{
		template <class T, class U>
		struct ConversionHelper
		{
			typedef char Small;
			struct Big { char dummy[2]; };
			static Big   Test(...);
			static Small Test(U);
			static T MakeT();
		};
	}

	////////////////////////////////////////////////////////////////////////////////
	// class template Conversion
	// Figures out the conversion relationships between two types
	// Invocations (T and U are types):
	// a) Conversion<T, U>::exists
	// returns (at compile time) true if there is an implicit conversion from T
	// to U (example: Derived to Base)
	// b) Conversion<T, U>::exists2Way
	// returns (at compile time) true if there are both conversions from T
	// to U and from U to T (example: int to char and back)
	// c) Conversion<T, U>::sameType
	// returns (at compile time) true if T and U represent the same type
	//
	// Caveat: might not work if T and U are in a private inheritance hierarchy.
	////////////////////////////////////////////////////////////////////////////////

	template <class T, class U>
	struct Conversion
	{
		typedef Private::ConversionHelper<T, U> H;
#ifndef __MWERKS__
		enum { exists = sizeof(typename H::Small) == sizeof((H::Test(H::MakeT()))) };
#else
		enum { exists = false };
#endif
		enum { exists2Way = exists && Conversion<U, T>::exists };
		enum { sameType = false };
	};

	template <class T>
	struct Conversion<T, T>
	{
		enum { exists = 1, exists2Way = 1, sameType = 1 };
	};

	template <class T>
	struct Conversion<void, T>
	{
		enum { exists = 0, exists2Way = 0, sameType = 0 };
	};

	template <class T>
	struct Conversion<T, void>
	{
		enum { exists = 0, exists2Way = 0, sameType = 0 };
	};

	template <>
	struct Conversion<void, void>
	{
	public:
		enum { exists = 1, exists2Way = 1, sameType = 1 };
	};

	////////////////////////////////////////////////////////////////////////////////
	// class template SuperSubclass
	// Invocation: SuperSubclass<B, D>::value where B and D are types.
	// Returns true if B is a public base of D, or if B and D are aliases of the
	// same type.
	//
	// Caveat: might not work if T and U are in a private inheritance hierarchy.
	////////////////////////////////////////////////////////////////////////////////

	template <class T, class U>
	struct SuperSubclass
	{
		enum { value = (::GnT::Conversion<const volatile U*, const volatile T*>::exists &&
			!::GnT::Conversion<const volatile T*, const volatile void*>::sameType) };

		// Dummy enum to make sure that both classes are fully defined.
		enum{ dontUseWithIncompleteTypes = ( sizeof (T) == sizeof (U) ) };
	};

	template <>
	struct SuperSubclass<void, void>
	{
		enum { value = false };
	};

	template <class U>
	struct SuperSubclass<void, U>
	{
		enum { value = (::GnT::Conversion<const volatile U*, const volatile void*>::exists &&
			!::GnT::Conversion<const volatile void*, const volatile void*>::sameType) };

		// Dummy enum to make sure that both classes are fully defined.
		enum{ dontUseWithIncompleteTypes = ( 0 == sizeof (U) ) };
	};

	template <class T>
	struct SuperSubclass<T, void>
	{
		enum { value = (::GnT::Conversion<const volatile void*, const volatile T*>::exists &&
			!::GnT::Conversion<const volatile T*, const volatile void*>::sameType) };

		// Dummy enum to make sure that both classes are fully defined.
		enum{ dontUseWithIncompleteTypes = ( sizeof (T) == 0 ) };
	};

	////////////////////////////////////////////////////////////////////////////////
	// class template SuperSubclassStrict
	// Invocation: SuperSubclassStrict<B, D>::value where B and D are types.
	// Returns true if B is a public base of D.
	//
	// Caveat: might not work if T and U are in a private inheritance hierarchy.
	////////////////////////////////////////////////////////////////////////////////

	template<class T,class U>
	struct SuperSubclassStrict
	{
		enum { value = (::GnT::Conversion<const volatile U*, const volatile T*>::exists &&
			!::GnT::Conversion<const volatile T*, const volatile void*>::sameType &&
			!::GnT::Conversion<const volatile T*, const volatile U*>::sameType) };

		// Dummy enum to make sure that both classes are fully defined.
		enum{ dontUseWithIncompleteTypes = ( sizeof (T) == sizeof (U) ) };
	};

	template<>
	struct SuperSubclassStrict<void, void>
	{
		enum { value = false };
	};

	template<class U>
	struct SuperSubclassStrict<void, U>
	{
		enum { value = (::GnT::Conversion<const volatile U*, const volatile void*>::exists &&
			!::GnT::Conversion<const volatile void*, const volatile void*>::sameType &&
			!::GnT::Conversion<const volatile void*, const volatile U*>::sameType) };

		// Dummy enum to make sure that both classes are fully defined.
		enum{ dontUseWithIncompleteTypes = ( 0 == sizeof (U) ) };
	};

	template<class T>
	struct SuperSubclassStrict<T, void>
	{
		enum { value = (::GnT::Conversion<const volatile void*, const volatile T*>::exists &&
			!::GnT::Conversion<const volatile T*, const volatile void*>::sameType &&
			!::GnT::Conversion<const volatile T*, const volatile void*>::sameType) };

		// Dummy enum to make sure that both classes are fully defined.
		enum{ dontUseWithIncompleteTypes = ( sizeof (T) == 0 ) };
	};


}   // namespace GnT

#define LOKI_SUPERSUBCLASS(T, U) \
	::GnT::SuperSubclass<T,U>::value

#define LOKI_SUPERSUBCLASS_STRICT(T, U) \
	::GnT::SuperSubclassStrict<T,U>::value

#endif // GNTYPEMANIP_H
