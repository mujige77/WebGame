#include "GnMainPCH.h"
#include "GnStream.h"


const guint32 GnStream::msGenieVersion = GnStream::GetVersion(GENIE_MAJOR_VERSION,
	GENIE_MINOR_VERSION, GENIE_PATCH_VERSION, GENIE_INTERNAL_VERSION);

GnTStringMap<GnStreamHelper::CreateFunction>* GnStreamHelper::mCreateFunctions = NULL;

void GnStreamHelper::EBMStartup()
{
	mCreateFunctions = GnNew GnTStringMap<GnStreamHelper::CreateFunction>(30, false);
}

void GnStreamHelper::EBMShutdown()
{
	GnDelete mCreateFunctions;
}

GnStream::GnStream() : mFileVersion(GnStream::msGenieVersion)
{

}

GnStream::~GnStream()
{
	Close();
}

bool GnStream::Save(const gchar* pcFilePath)
{
	mpFile = GnFile::GetFile(pcFilePath, GnFile::WRITE_BIANRY);
	if( mpFile == NULL )
		return false;

	SaveStream( mFileVersion );
	return true;
}

bool GnStream::Load(const gchar* pcFilePath)
{
	mpFile = GnFile::GetFile(pcFilePath, GnFile::READ_BIANRY);
	if( mpFile == NULL )
		return false;

	LoadStream( mFileVersion );
	return true;
}

void GnStreamHelper::RegisterRTTIObject(gchar* pcName, CreateFunction pFunc)
{
#ifdef GNDEBUG
	CreateFunction existsFunc = NULL;
	bool isExists = mCreateFunctions->GetAt( pcName, existsFunc );
	GnAssert( isExists == false );
#endif
	mCreateFunctions->Insert( pcName, pFunc );
}

void GnStreamHelper::UnRegisterRTTIObject(gchar* pcName)
{
	mCreateFunctions->Remove(pcName);
}

void GnStreamHelper::SetRTTICreateFunction(gchar* pcName)
{
	mCreateFunctions->GetAt(pcName, mCreateFunction);
	GnAssert(mCreateFunction);
}

void GnStream::LoadBinary(gwchar*& val)
{
	gushort len = 0;
	LoadStream( len );
	if( len <= 0 )
	{
		val = NULL;
		return;
	}
	GnAssert( GnT::TypeTraits<gushort>::TestMax( len ) );
	val = GnAlloc(gwchar, len + 1);		
	mpFile->LoadBinary(val, sizeof(gwchar) * len);
	val[len] = '\0';
}

void GnStream::SaveBinary(const gwchar*& val)
{
	if( val == NULL )
		return;

	gushort len = (gushort)GnWStrlen(val);
	if( len <= 0 )
	{
		val = NULL;
		return;
	}
	GnAssert( GnT::TypeTraits<gushort>::TestMax( len ) );
	SaveStream( len );
	mpFile->SaveBinary(val, sizeof(gwchar) * len );
}

void GnStream::LoadBinary(gchar*& val)
{
	gushort len = 0;
	LoadStream( len );
	if( len <= 0 )
	{
		val = NULL;
		return;
	}
	GnAssert( GnT::TypeTraits<gushort>::TestMax( len ) );
	val = GnAlloc(gchar, len + 1);		
	mpFile->LoadBinary(val, sizeof(gchar) * len);
	val[len] = '\0';
}

void GnStream::SaveBinary(const gchar*& val)
{
	if( val == NULL )
		return;

	gushort len = (gushort)GnStrlen( val );
	if( len <= 0 )
	{
		val = NULL;
		return;
	}
	GnAssert( GnT::TypeTraits<gushort>::TestMax( len ) );
	SaveStream( len );
	mpFile->SaveBinary(val, sizeof(char) * len );
}