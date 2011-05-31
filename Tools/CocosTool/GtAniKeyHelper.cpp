#include "StdAfx.h"
#include "GtAniKeyHelper.h"

bool CreateAnimationKey(GnAnimationKeyManager::AniKey &useKey, guint iKeyType, gtuint size)
{
	switch( iKeyType )
	{
	case GnAnimationKey::TEGIDKEY:
		useKey.mAnimationKeys = GtObjectNew<GnTegIDKey>::CreateArray( size );
		break;
	default:
		GnAssert( false );
		return false;
	}	
	useKey.mNumKey = size;
	useKey.mKeyType = (GnAnimationKey::eKeyType)iKeyType;
	return true;
}



void DeleteKeys(guint iKeyType, GnAnimationKeyManager* pAnimationKeyManager
	, GnAnimationKeyManager::AniKey useKey)
{
	guint index = GetAniKey( iKeyType, pAnimationKeyManager, useKey );
	if( index != -1 )
	{
		GnAssert( index != -1 );
		return;
	}
	pAnimationKeyManager->GetAnimationKeys()->RemoveAt( index );
}

int GetAniKey(guint iKeyType, GnAnimationKeyManager* pAnimationKeyManager
	, GnAnimationKeyManager::AniKey& outKey)
{
	if( iKeyType >= GnAnimationKey::MAX_KEYTYPE )
		return -1;

	GnTPrimitiveArray<GnAnimationKeyManager::AniKey>* keys = pAnimationKeyManager->GetAnimationKeys();	
	bool findKey = false;
	GnAnimationKeyManager::AniKey key;
	gtuint i = 0;
	for( ; i < keys->GetSize() ; i++ )
	{
		key = keys->GetAt( i );
		if( key.mKeyType == GnAnimationKey::TEGIDKEY )
		{
			outKey = key;
			findKey = true;
			break;
		}
	}
	if( findKey == false )
		return -1;

	return i;
}

void AddTegIDKey(guint iKeyType, GnAnimationKeyManager* pAnimationKeyManager 
	, float keyTime, guint32 tegID)
{
	GnAssert( iKeyType == GnAnimationKey::TEGIDKEY );

	GnAnimationKeyManager::AniKey useKey;
	guint index = 0;
	guint aniKeyIndex = GetAniKey( iKeyType, pAnimationKeyManager, useKey );
	if( aniKeyIndex == -1 )
	{
		if( CreateAnimationKey( useKey, iKeyType, 1 ) == false )
			return;
		pAnimationKeyManager->GetAnimationKeys()->Add( useKey );
	}
	else
	{
		index = useKey.mNumKey;
		guint32 reSize = index + 1;
		GnAnimationKeyManager::AniKey tempKey;
		if( CreateAnimationKey( tempKey, iKeyType, reSize ) == false )
			return;

		GnTegIDKey* useTegIDKey = (GnTegIDKey*)useKey.mAnimationKeys;
		GnTegIDKey* tempTegIDKey = (GnTegIDKey*)tempKey.mAnimationKeys;
		for( gtuint i = 0 ; i < reSize ; i++ )
		{
			tempTegIDKey[i] = useTegIDKey[i];
		}
		GtObjectNew<GnTegIDKey>::DeleteArray( useTegIDKey );
		useKey = tempKey;
		pAnimationKeyManager->GetAnimationKeys()->SetAt( aniKeyIndex, useKey );
	}
	GnTegIDKey* useTegIDKey = (GnTegIDKey*)useKey.mAnimationKeys;
	useTegIDKey[index].SetKeyTime( keyTime );
	useTegIDKey[index].SetTegID( tegID );
}

void RemoveTegIDKey(guint iKeyType, GnAnimationKeyManager* pAnimationKeyManager, guint uiIndex)
{
	GnAssert( iKeyType == GnAnimationKey::TEGIDKEY );

	GnAnimationKeyManager::AniKey useKey;
	int keyIndex = GetAniKey( iKeyType, pAnimationKeyManager, useKey );
	if( keyIndex == -1 )
	{
		return;
	}

	guint32 numKey = useKey.mNumKey;
	useKey.mNumKey -= 1;
	if( useKey.mNumKey <= 0 )
	{
		DeleteKeys(iKeyType, pAnimationKeyManager, useKey);
		return;
	}

	GnTegIDKey* useTegIDKey = (GnTegIDKey*)useKey.mAnimationKeys;
	for( gtuint i = uiIndex, fill = uiIndex + 1; fill < numKey ; i++, fill++ )
	{
		useTegIDKey[i] = useTegIDKey[fill];
	}
	pAnimationKeyManager->GetAnimationKeys()->SetAt( keyIndex, useKey );
}