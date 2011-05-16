#include "GnToolLibPCH.h"
#include "GtSMTextureAniCtrl.h"
#include "GnSMTextureAniCtrl.h"


GtSMTextureAniCtrl::GtSMTextureAniCtrl(void)
{
}


GtSMTextureAniCtrl::~GtSMTextureAniCtrl(void)
{
	for( gtuint i = 0 ; i < mAniList.GetSize() ; i++ )
	{
		GnDelete mAniList[i];
	}
}

void GtSMTextureAniCtrl::InsertAniInfo(AniInfo* pInfo)
{
	mAniList.Add( pInfo );
}

void GtSMTextureAniCtrl::SetAniInfo(gtuint uiIndex, AniInfo* pInfo)
{
	mAniList.SetAt( uiIndex, pInfo );
}

GtSMTextureAniCtrl::AniInfo* GtSMTextureAniCtrl::GetAniInfo(gtuint uiIndex)
{
	return mAniList.GetAt( uiIndex );
}

void GtSMTextureAniCtrl::RemoveInfo(gtuint uiIndex)
{
	GnDelete mAniList.GetAt( uiIndex );
	mAniList.RemoveAtAndFillAll( uiIndex );
}

void GtSMTextureAniCtrl::RemoveAll()
{
	for( gtuint i = 0 ; i <  mAniList.GetSize() ; i++ )
	{
		if( mAniList[i] )
			GnDelete mAniList[i];
	}
	mAniList.RemoveAll();
}

bool GtSMTextureAniCtrl::ExistSaveData()
{
	return mAniList.GetSize() > 0;
}

GnTimeController* GtSMTextureAniCtrl::CreateGnTimeController()
{
	if( mAniList.GetSize() <= 0 )
		return NULL;

	GnSMTextureAniCtrl* textureAni = GnNew GnSMTextureAniCtrl( mAniList.GetSize() );
	for( gtuint i = 0 ; i < mAniList.GetSize() ; i++ )
	{
		GtSMTextureAniCtrl::AniInfo* info = mAniList.GetAt( i );
		GnTextureProperty* texProperty = GnNew GnTextureProperty( info->mTextureFilePath );
		textureAni->SetAniInfo( i, texProperty, info->mStartTime, info->mEndTime );
	}
	textureAni->SetTargetName( mTargetName );
	return textureAni;
}

GtSMTextureAniCtrl* GtSMTextureAniCtrl::CreateFromGnData(GnSMTextureAniCtrl* pGnTextureAni)
{
	GtSMTextureAniCtrl* gtTimectlr = GnNew GtSMTextureAniCtrl();

	gtTimectlr->SetTargetName( pGnTextureAni->GetTargetName() );
	for( gtuint i = 0 ; i < pGnTextureAni->GetAniInfoCount() ; i++ )
	{
		GnSMTextureAniCtrl::TextureAni* gnAniInfo = pGnTextureAni->GetAniInfo( i );		
		GtSMTextureAniCtrl::AniInfo* info = GnNew GtSMTextureAniCtrl::AniInfo();
		info->mStartTime = gnAniInfo->mStartTime;
		info->mEndTime = gnAniInfo->mEndTime;
		info->mTextureFilePath = gnAniInfo->mpsPrperty->GetTexture( 0 )->GetTextureFileName();
		gtTimectlr->mAniList.Add( info );
	}
	return gtTimectlr;
}

void GtSMTextureAniCtrl::SaveStream(const gchar* objectName, const gchar* basePath)
{
	for( gtuint i = 0 ; i < mAniList.GetSize() ; i++ )
	{
		GtSMTextureAniCtrl::AniInfo* info = mAniList.GetAt( i );		

		gchar fileName[GN_MAX_PATH] = { 0, };
		GnVerify( GnPath::GetFileNameA( info->mTextureFilePath, fileName, GN_MAX_PATH, true ) );	
		gchar copyFilePath[GN_MAX_PATH] = { 0, };
		GnStrcpy( copyFilePath, basePath, sizeof( copyFilePath ) );
		GnStrcat( copyFilePath, fileName, sizeof( copyFilePath ) );
		if( GnPath::CheckSamePathA( info->mTextureFilePath, copyFilePath ) == false )
		{
			BOOL ret =CopyFileA( info->mTextureFilePath, copyFilePath, true );
			ret = TRUE;
		}

		gchar filePath[GN_MAX_PATH] = { 0, };
		GnStrcpy( filePath, objectName, sizeof( filePath ) );
		GnStrcat( filePath, "\\", sizeof( filePath ) );
		GnStrcat( filePath, fileName, sizeof( filePath ) );
		info->mTextureFilePath = filePath;
	}
}

void GtSMTextureAniCtrl::LoadStream(const gchar* objectName, const gchar* basePath)
{

}