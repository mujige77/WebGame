#include "GnMeshPCH.h"
#include "GnAnimationKeyManager.h"

GnAnimationKeyManager::AniKey::AniKey() : mKeyType(GnAnimationKey::MAX_KEYTYPE)
	, mNumKey(0), mAnimationKeys( NULL )
{

}

GnAnimationKeyManager::~GnAnimationKeyManager()
{
	for( gtuint i = 0 ; i < mAnimationKeys.GetSize() ; i++ )
	{
		GnDelete[] mAnimationKeys.GetAt( i ).mAnimationKeys;
	}
}

void GnAnimationKeyManager::LoadStream(GnStream* pStream)
{
	guint8 keyTypeCount = 0;
	pStream->LoadStream( keyTypeCount );
	if( keyTypeCount > 0 )
	{
		mAnimationKeys.SetSize( (gtuint)keyTypeCount, 1 );
		for( gtuint i = 0 ; i < mAnimationKeys.GetAllocatedSize() ; i++ )
		{
			guint8 keyType = 0;
			guint32 numKey;
			pStream->LoadStream( keyType );
			pStream->LoadStream( numKey );
			GnAnimationKey::LoadFunction funcCreate 
				= GnAnimationKey::GetLoadFunction( (GnAnimationKey::eKeyType)keyType );

			AniKey saveKey;
			saveKey.mKeyType = (GnAnimationKey::eKeyType)keyType;
			saveKey.mNumKey = numKey;			
			saveKey.mAnimationKeys = funcCreate( pStream, numKey );
			mAnimationKeys.Add( saveKey );
		}
	}
	
}

void GnAnimationKeyManager::SaveStream(GnStream* pStream)
{
	guint8 keyTypeCount = mAnimationKeys.GetSize();
	pStream->SaveStream( keyTypeCount );
	for( gtuint i = 0 ; i < mAnimationKeys.GetSize() ; i++ )
	{
		AniKey saveKey = mAnimationKeys.GetAt( i );
		guint8 keyType = (guint8)saveKey.mKeyType;
		pStream->SaveStream( keyType );
		pStream->SaveStream( saveKey.mNumKey );
		GnAnimationKey::SaveFunction funcSave
			= GnAnimationKey::GetSaveFunction( (GnAnimationKey::eKeyType)saveKey.mKeyType );
		funcSave( pStream, saveKey.mNumKey, saveKey.mAnimationKeys );
	}
}
