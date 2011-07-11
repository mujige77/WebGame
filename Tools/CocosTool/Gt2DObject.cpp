#include "StdAfx.h"
#include "Gt2DObject.h"

GnImplementRTTI(Gt2DObject, GtObject);

Gt2DObject::Gt2DObject(void) : m2DObjectType( 0 )
{
}


Gt2DObject::~Gt2DObject(void)
{
}

void Gt2DObject::SetObjectName(const gchar* pcVal)
{
	GtObject::SetObjectName( pcVal );
	std::string fileName = pcVal;
	fileName += ".gm";
	SetGMFileName( fileName.c_str() );
}

bool Gt2DObject::SaveData(const gchar* pcBasePath)
{
	if( IsModifed() == false )
		return true;

	gchar sequenceBasePath[GN_MAX_PATH] = {0,};
	GnStrcpy( sequenceBasePath, GtToolSettings::GetWorkPath(), sizeof(sequenceBasePath) );
	GnStrcat( sequenceBasePath, gs2DObjectPath[Get2DObjectType()], sizeof(sequenceBasePath) );
	GnStrcat( sequenceBasePath, GetObjectName(), sizeof(sequenceBasePath) );	
	GnStrcat( sequenceBasePath, "/", sizeof(sequenceBasePath) );

	GtToolSettings::CreateDirectoryInWorkDirectory( gs2DObjectPath[Get2DObjectType()], GetObjectName() );

	ChangeTextureAniInfoFileName( sequenceBasePath );

	Get2DMeshObjecct()->SetName( GetObjectName() );
	std::string meshPath = sequenceBasePath;
	meshPath += GetGMFileName();
	GnObjectStream meshStream;	
	meshStream.InsertRootObjects( Get2DMeshObjecct() );
	GnVerify( meshStream.Save( meshPath.c_str() ) );
	meshStream.Close();
	return true;
}

bool Gt2DObject::LoadData()
{
	if( mGMFileName.Exists() )
	{
		gchar outPath[GN_MAX_PATH] = {0,};
		std::string fileName = gs2DObjectPath[Get2DObjectType()];
		fileName += GetObjectName();
		fileName += "/";
		fileName += GetGMFileName();

		if( mpsMesh== NULL )
		{
			GnObjectStream objStream;
			mpsMesh = Gn2DMeshObject::Create( fileName.c_str(), true );
			if( mpsMesh == NULL )
				return false;
		}
	}
	else
		return false;
	return true;
}

bool Gt2DObject::CreateData()
{
	mpsMesh = Gn2DMeshObject::Create( true );
	GnAssert( mpsMesh );
	if( mpsMesh )
		return true;

	return false;
}

void Gt2DObject::ChangeTextureAniInfoFileName(const gchar* pcBasePath)
{
	GnTimeController* ctrl = Get2DMeshObjecct()->GetTimeControllers();
	while( ctrl )
	{
		Gn2DTextureAniCtlr* textureCtrl = GnDynamicCast(Gn2DTextureAniCtlr, ctrl);
		if( textureCtrl )
		{
			gtuint size = textureCtrl->GetAniInfos()->GetSize();
			for( gtuint i = 0; i < size; i++ )
			{
				Gn2DTextureAniCtlr::TextureAniInfo* info = textureCtrl->GetAniInfos()->GetAt( i );

				std::string onlyFileName = GetOnlyFileNameAttachNumber( i ,info->GetTextureName() );
				std::string copyFilePath = pcBasePath;	
				copyFilePath += onlyFileName;
				if( GnPath::CheckSamePathA( info->GetTextureName(), copyFilePath.c_str() ) == false )
				{
					BOOL ret = CopyFileA( info->GetTextureName(), copyFilePath.c_str(), false );
					ret = TRUE;
				}

				std::string newFilePath = gs2DObjectPath[Get2DObjectType()];
				newFilePath += GetObjectName();
				newFilePath += "/";
				newFilePath += onlyFileName;
				info->SetTextureName( newFilePath.c_str() );
			}
		}
		ctrl = ctrl->GetNext();
	}
}