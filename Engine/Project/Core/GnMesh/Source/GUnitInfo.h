#ifndef Core_GUnitInfo_h
#define Core_GUnitInfo_h

#include "GInfoBasic.h"

class GUnitInfo : public GnMemoryObject
{
	class info
	{
	public:
		info(guint32 uiIndex = 0, guint32 uiLevel = 1) : mIndex( uiIndex ), mLevel( uiLevel )
		{}
	public:
		guint32 mIndex;
		guint32 mLevel;
	};
protected:
	GnTPrimitiveSet<GUnitInfo::info> mUintInfos;
	
public:
	inline bool GetUnitInfo(guint32 uiIndex, GUnitInfo::info& outInfo)
	{
		for ( gtuint i = 0 ; i < mUintInfos.GetSize() ; i++ )
		{
			if( mUintInfos.GetAt( i ).mIndex == uiIndex )
			{
				outInfo = mUintInfos.GetAt( i );
				return true;
			}
		}
		return false;
	}
	
	inline void AddUnitInfo(guint32 uiIndex, guint32 uiLevel)
	{
		GUnitInfo::info info( uiIndex, uiLevel );
		mUintInfos.Add( info );
	}
	
};

#endif
