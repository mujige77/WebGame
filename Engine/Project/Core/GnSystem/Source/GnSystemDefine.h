#ifndef GNSYSTEMDEFINE_H
#define GNSYSTEMDEFINE_H


#if (!defined(GNDEBUG) && !defined(GNLOG) && !defined(GNRELEASE))
#error Exactly one of GNDEBUG, GNRELEASE, or GNLOG must be defined.
#endif

#ifndef GNBUILD
#    if defined(GNDEBUG)
#        define GNBUILD 1
#    elif defined(GNLOG)
#        define GNBUILD 1
#    elif defined(GNRELEASE)
#        define GNBUILD 0
#    endif
#endif // GNBUILD

#ifndef GN_USE_MEMORY_MANAGEMENT
#    if defined(GNDEBUG)
#        define GN_USE_MEMORY_MANAGEMENT 1
#    elif defined(GNLOG)
#        define GN_USE_MEMORY_MANAGEMENT 1
#    elif defined(GNRELEASE)
#        define GN_USE_MEMORY_MANAGEMENT 0
#    endif
#endif // GN_USE_MEMORY_MANAGEMENT

#if defined(WIN32)

#   ifndef GNFORCEINLINE
#       if defined _MSC_VER >= 1200
#           define GNFORCEINLINE __forceinline
#       else
#           define GNFORCEINLINE __inline
#       endif
#   endif // #ifndef GNFORCEINLINE

#   define  GNNOOP __noop

#elif defined(__GNUC__) 

#   ifndef GNFORCEINLINE
#       if (__GNUC__ >= 4)
#           define GNFORCEINLINE __attribute__((always_inline))
#       else // if (__GNUC__ >= 4)
#           define GNFORCEINLINE __inline
#       endif // if (__GNUC__ >= 4)
#   endif // #ifndef GNFORCEINLINE

#   define  GNNOOP ((void)0)

#endif // defined(WIN32)

#if defined (__APPLE__)
#define GNRESTRICT __restrict
#else // #if defined (__APPLE__)
#define GNRESTRICT
#endif // #if defined (__APPLE__)

typedef int gint;
typedef unsigned int guint;
typedef long glong;
typedef unsigned long gulong;
typedef short gshort;
typedef unsigned short gushort;
typedef char gchar;
typedef signed char gschar;
typedef unsigned char guchar;

#if defined(WIN32)
typedef int8_t gint8;
typedef uint8_t guint8;
typedef int16_t gint16;
typedef uint16_t guint16;
typedef int32_t gint32;
typedef uint32_t guint32;
typedef int64_t gint64;
typedef uint64_t guint64;
#elif defined(__APPLE__)
	typedef int8_t gint8;
	typedef uint8_t guint8;
	typedef int16_t gint16;
	typedef uint16_t guint16;
	typedef int32_t gint32;
	typedef uint32_t guint32;
	typedef int64_t gint64;
	typedef uint64_t guint64;
#endif

typedef size_t gsize;
typedef wchar_t gwchar;

#if defined(GN64)

typedef INT64 gtint;
typedef UINT64 gtuint;
typedef LONG64 gtlong;
typedef ULONG64 gtulong;

#else //  defined(GN64)

typedef gint gtint;
typedef guint gtuint;
typedef glong gtlong;
typedef gulong gtulong;

#endif // defined(GN64)

#define CHAR_BIT      8         /* number of bits in a char */
#define GSCHAR_MIN   (-128)      /* minimum signed char value */
#define GSCHAR_MAX     127       /* maximum signed char value */
#define GUCHAR_MAX     0xff      /* maximum unsigned char value */

#define GWCHAR_MIN	0x0000
#define GWCHAR_MAX	0xffff

#ifndef _CHAR_UNSIGNED
#define GCHAR_MIN    SCHAR_MIN   /* mimimum char value */
#define GCHAR_MAX    SCHAR_MAX   /* maximum char value */
#else
#define GCHAR_MIN      0
#define GCHAR_MAX    UCHAR_MAX
#endif  /* _CHAR_UNSIGNED */

#define GMB_LEN_MAX    5             /* max. # bytes in multibyte char */
#define GSHORT_MIN    (-32768)        /* minimum (signed) short value */
#define GSHORT_MAX      32767         /* maximum (signed) short value */
#define GUSHORT_MAX     0xffff        /* maximum unsigned short value */
#define GINT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define GINT_MAX       2147483647    /* maximum (signed) int value */
#define GUINT_MAX      0xffffffff    /* maximum unsigned int value */
#define GLONG_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#define GLONG_MAX      2147483647L   /* maximum (signed) long value */
#define GULONG_MAX     0xffffffffUL  /* maximum unsigned long value */
#define GLLONG_MAX     9223372036854775807i64       /* maximum signed long long int value */
#define GLLONG_MIN   (-9223372036854775807i64 - 1)  /* minimum signed long long int value */
#define GULLONG_MAX    0xffffffffffffffffui64       /* maximum unsigned long long int value */

#define GINT8_MIN     (-127i8 - 1)    /* minimum signed 8 bit value */
#define GINT8_MAX       127i8         /* maximum signed 8 bit value */
#define GUINT8_MAX      0xffui8       /* maximum unsigned 8 bit value */

#define GINT16_MIN    (-32767i16 - 1) /* minimum signed 16 bit value */
#define GINT16_MAX      32767i16      /* maximum signed 16 bit value */
#define GUINT16_MAX     0xffffui16    /* maximum unsigned 16 bit value */

#define GINT32_MIN    (-2147483647i32 - 1) /* minimum signed 32 bit value */
#define GINT32_MAX      2147483647i32 /* maximum signed 32 bit value */
#define GUINT32_MAX     0xffffffffui32 /* maximum unsigned 32 bit value */

#define GINT64_MIN    (-9223372036854775807i64 - 1) /* minimum signed 64 bit value */
#define GINT64_MAX      9223372036854775807i64 /* maximum signed 64 bit value */
#define GUINT64_MAX     0xffffffffffffffffui64 /* maximum unsigned 64 bit value */

#if     _INTEGRAL_MAX_BITS >= 128
/* minimum signed 128 bit value */
#define _I128_MIN   (-170141183460469231731687303715884105727i128 - 1)
/* maximum signed 128 bit value */
#define _I128_MAX     170141183460469231731687303715884105727i128
/* maximum unsigned 128 bit value */
#define _UI128_MAX    0xffffffffffffffffffffffffffffffffui128
#endif

#define GnMax(a,b)  (((a) > (b)) ? (a) : (b))
#define GnMin(a,b)  (((a) < (b)) ? (a) : (b))

#ifdef WIN32

typedef HWND GnWindowHandle;
typedef HINSTANCE GnInstance;

GNSYSTEM_ENTRY GNFORCEINLINE gint32 GnAtomicIncrement(gint32& i32Value)
{
	return InterlockedIncrement((LONG*)&i32Value);
}
GNSYSTEM_ENTRY GNFORCEINLINE gint32 GnAtomicDecrement(gint32& i32Value)
{
	return InterlockedDecrement((LONG*)&i32Value);
}
GNSYSTEM_ENTRY GNFORCEINLINE guint32 GnAtomicIncrement(guint32& ui32Value)
{
	return InterlockedIncrement((LONG*)&ui32Value);
}
GNSYSTEM_ENTRY GNFORCEINLINE guint32 GnAtomicDecrement(guint32& ui32Value)
{
	return InterlockedDecrement((LONG*)&ui32Value);
}

#else // WIN32

GNSYSTEM_ENTRY GNFORCEINLINE gint32 NiAtomicIncrement(gint32& i32Value)
{
	return __sync_fetch_and_add((LONG*)&i32Value, 1);
}
GNSYSTEM_ENTRY GNFORCEINLINE gint32 NiAtomicDecrement(gint32& i32Value)
{
	return __sync_fetch_and_sub ((LONG*)&i32Value, 1);
}
GNSYSTEM_ENTRY GNFORCEINLINE guint32 NiAtomicIncrement(guint32& ui32Value)
{
	return __sync_fetch_and_add((LONG*)&ui32Value);
}
GNSYSTEM_ENTRY GNFORCEINLINE guint32 NiAtomicDecrement(guint32& ui32Value)
{
	return __sync_fetch_and_sub((LONG*)&ui32Value);
}

#endif // WIN32


#endif // GNSYSTEMDEFINE_H
