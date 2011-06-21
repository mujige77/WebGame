#include "GnMainPCH.h"
#include "GnObjectStream.h"

static const guint32 NULL_LINKID = GUINT32_MAX - 1;

GnObjectStream::GnObjectStream() : mLinkIndex(0), mLinkBlockIndex(0)
{

}

bool GnObjectStream::Load(const gchar* pcFilePath)
{
	RemoveAllObjects();

	if( GnStream::Load(pcFilePath) == false )
		return false;

	if( LoadHeader() == false )
		return false;

	if( LoadRTTI() == false )
		return false;

	LoadFixedStrings();

	if( LoadObject() == false )
	{
		ResetLoadDatas();
		return false;
	}

	LoadRootObject();

	ResetLoadDatas();
	return true;
}

bool GnObjectStream::Save(const gchar* pcFilePath)
{
	if( GnStream::Save(pcFilePath) == false )
		return false;

	RegisterObject();

	SaveHeader();

	SaveRTTI();

	SaveFixedStrings();

	SaveObject();

	SaveRootObject();

	mObjectLists.RemoveAll();
	mRegObjects.RemoveAll();
	return true;
}

bool GnObjectStream::LoadHeader()
{
	guint32 objectCount = 0;
	LoadStream(objectCount);

	if( objectCount <= 0 )
		return false;

	mObjectLists.SetSize(objectCount);
	return true;
}

void GnObjectStream::RegisterObject()
{
	for( gtuint i = 0 ; i < mRootLevelObjects.GetSize() ; i++ )
	{
		GnObject* object = mRootLevelObjects.GetAt(i);
		GnAssert(object);
		object->RegisterSaveObject(this);
	}
}

void GnObjectStream::SaveHeader()
{
	guint32 objectCount = (guint32)mObjectLists.GetSize();
	SaveStream(objectCount);
}

bool GnObjectStream::LoadRTTI()
{
	gushort rttiCount = 0;
	LoadStream(rttiCount);

	GnStreamHelper* rttiHelper = GnNew GnStreamHelper[rttiCount];
	for ( gushort i = 0 ; i < rttiCount ; i++ )
	{
		gchar str[MAX_RTTINAME] = {0,};
		LoadRTTiString(str);
		rttiHelper[i].SetRTTICreateFunction(str);
	}

	for ( gtuint i = 0 ; i < mObjectLists.GetAllocatedSize() ; i++)
	{
		gushort numRTTI = 0;
		LoadStream(numRTTI);
		GnAssert(numRTTI < rttiCount);

		GnObject* object = rttiHelper[numRTTI].CreateObject();

		mObjectLists.SetAt(i, object);
	}

	GnDelete[] rttiHelper;
	return true;
}

void GnObjectStream::SaveRTTI()
{
	gchar rttiName[MAX_RTTINAME] = {0,};
	GnTStringMap<gushort> rttis;	
	for( gtuint i = 0 ; i < mObjectLists.GetSize() ; i++ )
	{
		GnObject* object = mObjectLists.GetAt(i);
		object->GetRTTINameForStream(rttiName, MAX_RTTINAME);
		if( rttis.Find(rttiName) == false )
		{
			GnAssert( rttis.Count() < UCHAR_MAX );
			rttis.SetAt( rttiName, rttis.Count() );
		}
	}
	gushort rttiCount = rttis.Count();	
	SaveStream( rttiCount );

	const gchar** tempSaveRTTI = GnAlloc( const gchar*, rttiCount );
	GnTStringMap<gushort>::Iterator iter;
	rttis.GetFirstIter(iter);
	while(iter.Valid())
	{
		GnTStringMap<gushort>::Entry item = iter.Item();		
		tempSaveRTTI[item.m_data] = item.m_key;
		rttis.GetNextIter(iter);
	}

	for( gushort i = 0 ; i < rttiCount ; i++ )
	{
		SaveStream( tempSaveRTTI[i] );
	}

	// RTTI \u03c0\257\273\243\u220f\u220f \277\u02d9\277\302\253\u0153\u221e\314 \261\u25ca\u03c0\257\273\243\u220f\266 \u2248\u2030\245\316\u2211\u0152 \u2211\u0152\265\u02d8\u03a9\u221a \370\277\u222b\315\241\337\u2206\306\u220f\266 \252\u02dd\272\u222b\253\u2014\245\u0178.
	for( gtuint i = 0 ; i < mObjectLists.GetSize() ; i++ )
	{
		gushort numRTTI = 0;
		GnObject* object = mObjectLists.GetAt(i);
		GnVerify( object->GetRTTINameForStream(rttiName, MAX_RTTINAME) );
		GnVerify( rttis.GetAt(rttiName, numRTTI) );
		GnAssert( numRTTI < rttiCount );
		SaveStream(numRTTI);
	}
}

void GnObjectStream::LoadFixedStrings()
{
	guint16 count = 0;
	LoadStream( count );
	mFixedStrings.SetSize( count );	

	guint16 maxLength = 0;
	LoadStream(maxLength);	
	gchar* fixedStr = GnAlloc( gchar, maxLength+1);	

	for( guint32 i = 0 ; i < count ; i++ )
	{
		guint16 len = 0;
		LoadStream( len );
		LoadStreams( fixedStr, len );
		fixedStr[len] = '\\0';
		mFixedStrings.Add( GnSimpleString(fixedStr) );
	}

	GnFree( fixedStr );
}

void GnObjectStream::SaveFixedStrings()
{
	guint16 size = mFixedStrings.GetSize();
	SaveStream( size );

	guint16 maxLength = 0;
	guint16 len = 0;
	for( gtuint i = 0; i < mFixedStrings.GetSize(); i++ )
	{
		const GnSimpleString& str = mFixedStrings.GetAt(i);
		len = str.GetLength();
		if( len > maxLength )
			maxLength = len;
	}

	SaveStream(maxLength);

	for( gtuint i = 0; i < mFixedStrings.GetSize(); i++ )
	{
		const GnSimpleString& str = mFixedStrings.GetAt(i);
		const char* strHandle = (const char*)str;
		SaveStream(strHandle);
	}
}

void GnObjectStream::SaveObject()
{
	// save list of objects
	for (unsigned int i = 0; i < mObjectLists.GetSize(); i++)
	{
		GnObject* object = mObjectLists.GetAt(i);
		object->SaveStream(this);
	}
}

bool GnObjectStream::LoadObject()
{
	// save list of objects
	for (unsigned int i = 0; i < mObjectLists.GetSize(); i++)
	{
		GnObject* object = mObjectLists.GetAt(i);
		object->LoadStream(this);
	}

	// save list of objects
	for (unsigned int i = 0; i < mObjectLists.GetSize(); i++)
	{
		GnObject* object = mObjectLists.GetAt(i);
		object->LinkObject(this);
	}
	return true;
}

void GnObjectStream::SaveRootObject()
{
	guint32 numRoot = mRootLevelObjects.GetSize();
	SaveStream( numRoot );

	for( guint32 i = 0 ; i < numRoot ; i++ )
	{
		SaveLinkID( mRootLevelObjects.GetAt( i ) );
	}
}

bool GnObjectStream::LoadRootObject()
{
	guint32 numRoot = 0;
	LoadStream( numRoot );
	mRootLevelObjects.SetSize( numRoot );

	for( guint32 i = 0 ; i < numRoot ; i++ )
	{
		GnObject* object = NULL;
		guint32 linkID = NULL_LINKID;	
		LoadStream(  linkID );
		if( linkID != NULL_LINKID )
		{
			GnAssert( linkID < mObjectLists.GetSize() );
			object = mObjectLists.GetAt( linkID );
		}
		mRootLevelObjects.SetAt( i, object );
	}
	return true;
}

bool GnObjectStream::RegisterSaveObject(GnObject* pObject)
{
	guint32 linkID = NULL_LINKID;
	if( mRegObjects.GetAt(pObject, linkID) )
		return false;

	linkID = mObjectLists.GetSize();
	mRegObjects.Insert(pObject, linkID);
	mObjectLists.Add(pObject);
	return true;
}

bool GnObjectStream::RegisterFixedString(GnSimpleString& str)
{
	if( GetStringID(str) == NULL_LINKID )
	{
		mFixedStrings.Add(str);
	}
	return true;
}

void GnObjectStream::LoadRTTiString(gchar* pcStr)
{
	gushort len = 0;
	mpFile->LoadBinary(&len, sizeof(gushort));
	mpFile->LoadBinary(pcStr, len);
	//pcStr[len] = '\\0';
}

guint32 GnObjectStream::GetLinkID(const GnObject* pObject)
{
	guint32 linkID = NULL_LINKID;
	if( pObject == NULL )
		return linkID;

	mRegObjects.GetAt(pObject, linkID);
	return linkID;
}

void GnObjectStream::LoadFixedString(GnSimpleString& str)
{
	guint32 linkID = NULL_LINKID;	
	LoadStream(linkID);
	if( linkID == NULL_LINKID )
		str = NULL;
	else
	{
		GnAssert( mFixedStrings.GetSize() > linkID );
		str = mFixedStrings.GetAt(linkID);
	}
}

void GnObjectStream::SaveFixedString(const GnSimpleString& str)
{
	if( !str.Exists() )
	{
		guint32 linkID = NULL_LINKID;
		SaveStream( linkID );
	}

	guint32 linkID = GetStringID( str );
	GnAssert( linkID != NULL_LINKID );
	SaveStream(linkID);
}

guint32 GnObjectStream::GetStringID(const GnSimpleString& str)
{
	if ( str.Exists() )
	{
		for( guint32 ui = 0; ui < mFixedStrings.GetSize(); ui++ )
		{
			if (str == mFixedStrings.GetAt(ui))
				return ui;
		}
	}
	return NULL_LINKID;
}

GnObject* GnObjectStream::GetObjectFromLinkID()
{
	GnAssert( mLinkIndex < mLinkIDs.GetSize() );

	unsigned int linkID = mLinkIDs.GetAt( mLinkIndex++ );

	if (linkID == NULL_LINKID)
		return NULL;

	GnAssert( linkID < mObjectLists.GetSize() );
	return mObjectLists.GetAt( linkID );
}

guint32 GnObjectStream::LoadMultipleLinkIDs()
{
	guint32 uiNum = NULL_LINKID;
	LoadStream( uiNum );

	mMultiLinkIDBlocks.Add( uiNum );
	for (unsigned int ui = 0; ui < uiNum; ui++)
		LoadLinkID();
	return uiNum;
}

void GnObjectStream::RemoveAllObjects()
{
	mRootLevelObjects.RemoveAll();
	mFixedStrings.RemoveAll();
}

void GnObjectStream::ResetLoadDatas()
{
	mObjectLists.RemoveAll();
	mLinkIDs.RemoveAll();
	mMultiLinkIDBlocks.RemoveAll();
	mLinkIndex = 0;
	mLinkBlockIndex = 0;
}