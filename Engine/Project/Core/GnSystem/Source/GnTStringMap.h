#ifndef GNSTRINGMAP_H
#define GNSTRINGMAP_H
#include "GnTMap.h"

template<class KeyType>
class GnTStringMapHash
{
public:
	inline static gtuint HashIndex( KeyType key )
	{
		return GnStrlen(key);
	}
};


template<class KeyType>
class GnTStringEqual
{
public:
	inline static bool IsEqual(KeyType key1, KeyType key2)
	{
		return GnStrcmp(key1, key2) == 0;
	}
};

template
<
	class T,	
	template<class> class DataDeallocate = GnDefaultDeallocate,
	template<class> class MapHash = GnTStringMapHash,
	template<class> class MapEqual = GnTStringEqual
>
class GnTStringMap;

template
<
	class DataType,	
	template<class> class DataDeallocate,
	template<class> class MapHash,
	template<class> class MapEqual
>
class GnTStringMap : public GnTMap<const gchar*, DataType, DataDeallocate, MapHash, MapEqual>
{
	typedef typename GnTMap<const gchar*, DataType, DataDeallocate, MapHash, MapEqual>::Entry stringEntry;
protected:
	bool mCopy;
	
public:
	GnTStringMap(gtuint size = 30, bool bCopy = true) : GnTMap<const gchar*, DataType, DataDeallocate
		, MapHash, MapEqual>(size), mCopy(bCopy)
	{

	}
	virtual void SetValue(stringEntry& item, const char* key, DataType val)
	{
		if (mCopy)
		{
			unsigned int len = GnStrlen(key) + 1;
			item.m_key = GnAlloc(gchar, len);
			GnStrcpy((gchar*)item.m_key, key, len);
		}
		else
		{
			item.m_key = key;
		}
		item.m_data = val;
	}

	virtual void ClearValue(stringEntry& item)
	{
		if (mCopy)
			GnFree((gchar*)item.m_key);
	}
};

#endif // GNSTRINGMAP_H