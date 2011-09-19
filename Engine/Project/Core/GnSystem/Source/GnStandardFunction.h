#ifndef Core_GnStandardFunction_h
#define Core_GnStandardFunction_h

static inline void GnSrand(gtuint uiRandom)
{
	srand( uiRandom );
}

static inline gint GnRand()
{
	return rand();
}

template<typename T>
static void GnShuffleArray(T* pArray, gtuint uiCount)
{
	for ( gtuint i = 0; i < uiCount; i++ )
	{
		int r = i + ( GnRand() % ( uiCount - i ) ) ;
		T temp = pArray[i];
		pArray[i] = pArray[r];
		pArray[r] = temp;
	}
}

template<typename T>
static void GnShuffle(T cArray, gtuint uiCount)
{
	for ( gtuint i = 0; i < uiCount; i++ )
	{
		int r = i + ( GnRand() % ( uiCount - i ) ) ;
		T temp = cArray.GetAt( i );
		cArray.SetAt( i, cArray.GetAt( r ) );
		cArray.SetAt( r, temp );
	}
}

#endif
