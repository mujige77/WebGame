#include "GnMeshPCH.h"
#include "GnAnimationKey.h"

GnAnimationKey::LoadFunction GnAnimationKey::msLoadFunction[GnAnimationKey::MAX_KEYTYPE];
GnAnimationKey::SaveFunction GnAnimationKey::msSaveFunction[GnAnimationKey::MAX_KEYTYPE];
GnAnimationKey::DestroyFunction GnAnimationKey::msDestroyFunction[GnAnimationKey::MAX_KEYTYPE];

GnAnimationKey::LoadFunction GnAnimationKey::GetLoadFunction(eKeyType eType)
{
	GnAssert( eType != MAX_KEYTYPE );
	return msLoadFunction[eType];
}

GnAnimationKey::SaveFunction GnAnimationKey::GetSaveFunction(eKeyType eType)
{
	GnAssert( eType != MAX_KEYTYPE );
	return msSaveFunction[eType];
}

GnAnimationKey::DestroyFunction GnAnimationKey::GetDestroyFunction(eKeyType eType)
{
	GnAssert( eType != MAX_KEYTYPE );
	return msDestroyFunction[eType];
}

void GnAnimationKey::RegLoadFunction(eKeyType eType, LoadFunction funcCreate)
{
	GnAssert( eType != MAX_KEYTYPE );
	msLoadFunction[eType] = funcCreate;
}

void GnAnimationKey::RegSaveFunction(eKeyType eType, SaveFunction funcCreate)
{
	GnAssert( eType != MAX_KEYTYPE );
	msSaveFunction[eType] = funcCreate;
}

void GnAnimationKey::RegDestroyFunction(eKeyType eType, DestroyFunction funcCreate)
{
	GnAssert( eType != MAX_KEYTYPE );
	msDestroyFunction[eType] = funcCreate;
}

void GnAnimationKey::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( mKeyTime );
}

void GnAnimationKey::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( mKeyTime );
}
