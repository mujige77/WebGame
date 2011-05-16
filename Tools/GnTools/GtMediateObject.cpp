#include "StdAfx.h"
#include "GtMediateObject.h"

using namespace std;
std::multimap<gtuint, GtMediateObject*> GtMediateObject::mMediate;

GtMediateObject::GtMediateObject(void)
{
}


GtMediateObject::~GtMediateObject(void)
{
}

void GtMediateObject::AttachNeedMessage(gtuint messageIndex)
{
	MediateMapIter iter;
	if( GetIterFromMessageObjectInfo( messageIndex, this, iter ) )
	{
		GnAssert( false );
		return;
	}
	mMediate.insert( make_pair(messageIndex, this ) );
}

bool GtMediateObject::GetIterFromMessageObjectInfo(gtuint messageIndex, GtMediateObject* pObject, MediateMapIter& outIter)
{
	pair<MediateMapIter, MediateMapIter> iterPair = mMediate.equal_range( messageIndex );
	for( outIter = iterPair.first ; outIter != iterPair.second ; outIter++)
	{
		if( outIter->second == pObject )
			return true;
	}
	return false;
}

void GtMediateObject::SendMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pSanderInfo)
{
	pair<MediateMapIter, MediateMapIter> iterPair = mMediate.equal_range( messageIndex );
	MediateMapIter iter;
	for( iter = iterPair.first ; iter != iterPair.second ; iter++)
	{
		iter->second->ReceiveMediateMessage( messageIndex, pSanderInfo );
	}
}