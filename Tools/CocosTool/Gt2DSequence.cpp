#include "StdAfx.h"
#include "Gt2DSequence.h"

GnImplementRTTI(Gt2DSequence, Gn2DSequence);

Gt2DSequence::Gt2DSequence(void)
{
}


Gt2DSequence::~Gt2DSequence(void)
{
}

void Gt2DSequence::ChangeTextureFile(gtuint uiAniIndex, gtuint aniInfoIndex, const char* pcFileName)
{
	SetModifed( true );
	Gn2DTextureAni* ani = GetTextureAni( uiAniIndex );
	Gn2DTextureAni::TextureAniInfo* textureAniInfo =
		(Gn2DTextureAni::TextureAniInfo*)ani->GetAniInfo( aniInfoIndex );
	textureAniInfo->SetTextureName( pcFileName );

	ani->RemoveData();
}

void Gt2DSequence::ChangeTime(gtuint uiAniIndex, float fTime)
{
	SetModifed( true );
	Gn2DTextureAni* ani = GetTextureAni( uiAniIndex );
	ani->SetAniSpeed( fTime );
}

bool Gt2DSequence::SaveData(const gchar* folderName, const gchar* pcBasePath)
{
	std::string fullFilePath = GtToolSettings::GetWorkPath();
	fullFilePath += mFileName.GetAciiString();

	for( gtuint i = 0 ; i < GetSequence()->GetTextureAnis().GetSize() ; i++ )
	{
		Gn2DTextureAni* ani = GetSequence()->GetTextureAnis().GetAt( i );
		
		for( gtuint j = 0 ; j < ani->GetAniInfoCount() ; j++ )
		{
			Gn2DTextureAni::TextureAniInfo* aniInfo = (Gn2DTextureAni::TextureAniInfo*)ani->GetAniInfo( j );
			GtNumberString number;
			number.SetNumber( 3, GetSequence()->GetID() );
			GtConvertString convert = number.GetString().c_str();
			convert += _T("_");

			gchar name[GN_MAX_PATH] = { 0, };
			GnVerify( GnPath::GetFileNameA( aniInfo->GetTextureName(), name, GN_MAX_PATH, true ) );
			std::string fileName = name;
			if( fileName.find( convert.GetAciiString() ) == std::string::npos )
			{
				fileName = convert.GetAciiString();
				fileName += name;
			}

			std::string copyFilePath = pcBasePath;	
			copyFilePath += fileName;
			if( GnPath::CheckSamePathA( aniInfo->GetTextureName(), copyFilePath.c_str() ) == false )
			{
				BOOL ret = CopyFileA( aniInfo->GetTextureName(), copyFilePath.c_str(), false );
				ret = TRUE;
			}
			std::string filePath = folderName;
			filePath += "\\";
			filePath += fileName;
			aniInfo->SetTextureName( filePath.c_str() );
		}
	}
	
	GnObjectStream objectStream;
	objectStream.InsertRootObjects( mpSequence );

	GnVerify( objectStream.Save( fullFilePath.c_str() ) );
	objectStream.Close();
	return true;
}

void Gt2DSequence::SetObjectName(const gchar* pcVal)
{
	GtObject::SetObjectName( pcVal );
	mFileName = pcVal;
	mFileName += _T(".ga");
}