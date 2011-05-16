#ifdef WIN32
    #include <cassert>
#else // #ifdef WIN32
    #include <assert.h>
#endif // #ifdef WIN32

#ifdef GNDEBUG
    #define GnAssert assert
#else // #ifdef GNDEBUG
    #define GnAssert GNNOOP
#endif

#ifdef GNDEBUG
#define GnVerify assert
#else // #ifdef GNDEBUG
#define GnVerify 
#endif

