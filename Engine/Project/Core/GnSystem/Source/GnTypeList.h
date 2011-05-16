#include "GnTOther.h"

namespace GnT
{
	template <class T, class U>
	struct TypeList
	{
		typedef T Head;
		typedef U Tail;
	};

	template < class TList, class T > struct IndexOf;

	template < class T >
	struct IndexOf< _NullType, T >
	{
		enum { value = -1 };
	};

	template < class T, class Tail >
	struct IndexOf< TypeList< T, Tail >, T >
	{
		enum { value = 0 };
	};

	template < class Head, class Tail, class T >
	struct IndexOf< TypeList< Head, Tail >, T >
	{
	private:
		enum { temp = IndexOf<Tail, T>::value };

	public:
		enum { value = (temp == -1 ? -1 : 1 + temp) };
	};
}


#define GNTYPELIST_1(T1) ::GnT::TypeList< T1, ::GnT::_NullType >

#define GNTYPELIST_2(T1, T2) ::GnT::TypeList<T1, GNTYPELIST_1(T2) >

#define GNTYPELIST_3(T1, T2, T3) ::GnT::TypeList<T1, GNTYPELIST_2(T2, T3) >

#define GNTYPELIST_4(T1, T2, T3, T4) \
	::GnT::TypeList<T1, GNTYPELIST_3(T2, T3, T4) >

#define GNTYPELIST_5(T1, T2, T3, T4, T5) \
	::GnT::TypeList<T1, GNTYPELIST_4(T2, T3, T4, T5) >

#define GNTYPELIST_6(T1, T2, T3, T4, T5, T6) \
	::GnT::TypeList<T1, GNTYPELIST_5(T2, T3, T4, T5, T6) >

#define GNTYPELIST_7(T1, T2, T3, T4, T5, T6, T7) \
	::GnT::TypeList<T1, GNTYPELIST_6(T2, T3, T4, T5, T6, T7) >

#define GNTYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) \
	::GnT::TypeList<T1, GNTYPELIST_7(T2, T3, T4, T5, T6, T7, T8) >

#define GNTYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
	::GnT::TypeList<T1, GNTYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9) >

#define GNTYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) \
	::GnT::TypeList<T1, GNTYPELIST_9(T2, T3, T4, T5, T6, T7, T8, T9, T10) >

#define GNTYPELIST_11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) \
	::GnT::TypeList<T1, GNTYPELIST_10(T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) >

#define GNTYPELIST_12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) \
	::GnT::TypeList<T1, GNTYPELIST_11(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12) >

#define GNTYPELIST_13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) \
	::GnT::TypeList<T1, GNTYPELIST_12(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13) >

#define GNTYPELIST_14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14) \
	::GnT::TypeList<T1, GNTYPELIST_13(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14) >

#define GNTYPELIST_15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15) \
	::GnT::TypeList<T1, GNTYPELIST_14(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15) >

#define GNTYPELIST_16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16) \
	::GnT::TypeList<T1, GNTYPELIST_15(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16) >

#define GNTYPELIST_17(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17) \
	::GnT::TypeList<T1, GNTYPELIST_16(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17) >

#define GNTYPELIST_18(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18) \
	::GnT::TypeList<T1, GNTYPELIST_17(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18) >

#define GNTYPELIST_19(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19) \
	::GnT::TypeList<T1, GNTYPELIST_18(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19) >

#define GNTYPELIST_20(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) \
	::GnT::TypeList<T1, GNTYPELIST_19(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) >

#define GNTYPELIST_21(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) \
	::GnT::TypeList<T1, GNTYPELIST_20(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) >

#define GNTYPELIST_22(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) \
	::GnT::TypeList<T1, GNTYPELIST_21(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) >

#define GNTYPELIST_23(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) \
	::GnT::TypeList<T1, GNTYPELIST_22(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) >

#define GNTYPELIST_24(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) \
	::GnT::TypeList<T1, GNTYPELIST_23(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) >

#define GNTYPELIST_25(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) \
	::GnT::TypeList<T1, GNTYPELIST_24(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25) >

#define GNTYPELIST_26(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26) \
	::GnT::TypeList<T1, GNTYPELIST_25(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26) >

#define GNTYPELIST_27(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27) \
	::GnT::TypeList<T1, GNTYPELIST_26(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27) >

#define GNTYPELIST_28(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27, T28) \
	::GnT::TypeList<T1, GNTYPELIST_27(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27, T28) >

#define GNTYPELIST_29(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27, T28, T29) \
	::GnT::TypeList<T1, GNTYPELIST_28(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27, T28, T29) >

#define GNTYPELIST_30(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) \
	::GnT::TypeList<T1, GNTYPELIST_29(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
	T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) >
