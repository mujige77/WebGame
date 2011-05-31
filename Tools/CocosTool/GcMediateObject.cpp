#include "StdAfx.h"
#include "GcMediateObject.h"

using namespace std;
std::multimap<gtuint, GcMediateObject*> GcMediateObject::mMediate;

GcMediateObject::GcMediateObject(void)
{
}


GcMediateObject::~GcMediateObject(void)
{
}

void GcMediateObject::AttachNeedMessage(gtuint messageIndex)
{
	MediateMapIter iter;
	if( GetIterFromMessageObjectInfo( messageIndex, this, iter ) )
	{
		GnAssert( false );
		return;
	}
	mMediate.insert( make_pair(messageIndex, this ) );
}

void GcMediateObject::DetachNeedMessage(gtuint messageIndex)
{
	pair<MediateMapIter, MediateMapIter> iterPair = mMediate.equal_range( messageIndex );
	MediateMapIter iter;
	for( iter = iterPair.first ; iter != iterPair.second ; iter++)
	{
		if( iter->second == this )
		{
			mMediate.erase( iter );
			break;
		}
	}
}

bool GcMediateObject::GetIterFromMessageObjectInfo(gtuint messageIndex, GcMediateObject* pObject, MediateMapIter& outIter)
{
	pair<MediateMapIter, MediateMapIter> iterPair = mMediate.equal_range( messageIndex );
	for( outIter = iterPair.first ; outIter != iterPair.second ; outIter++)
	{
		if( outIter->second == pObject )
			return true;
	}
	return false;
}

void GcMediateObject::SendMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage)
{
	pair<MediateMapIter, MediateMapIter> iterPair = mMediate.equal_range( messageIndex );
	MediateMapIter iter;
	for( iter = iterPair.first ; iter != iterPair.second ; iter++)
	{
		iter->second->ReceiveMediateMessage( messageIndex, pMessage );
	}
}