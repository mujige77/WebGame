#include "GnMeshPCH.h"
#include "GnTegIDKey.h"

GnImplementCreateAnimationKey(GnTegIDKey, TEGIDKEY);
GnAnimationKey* GnTegIDKey::LoadFromStream(GnStream* pStream, guint32 numKey)
{
	GnTegIDKey* key = GnNew GnTegIDKey[numKey];
	for( gtuint i = 0 ; i < numKey ; i++ )
	{
		key[i].LoadStream( pStream );
	}
	return key;
}

void GnTegIDKey::SaveToStream(GnStream* pStream, guint32 numKey, GnAnimationKey* pKeys)
{
	GnTegIDKey* tegIDKey = (GnTegIDKey*)pKeys;
	for( guint32 i = 0 ; i < numKey ; i++ )
	{
		tegIDKey[i].SaveStream( pStream );
	}
}

void GnTegIDKey::LoadStream(GnStream* pStream)
{
	GnAnimationKey::LoadStream( pStream );

	pStream->LoadStream( mTegID );
}

void GnTegIDKey::SaveStream(GnStream* pStream)
{
	GnAnimationKey::SaveStream( pStream );

	pStream->SaveStream( mTegID );
}