#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnIButton.h"
#include "GnICoolTime.h"

GnIButton::GnIButton(const gchar* pcDefaultImage, const gchar* pcClickImage
	, const gchar* pcDisableImage, GnIButton::eButtonType eDefaultType) : mpCoolTime(NULL)
{
	switch( (gint)eDefaultType )
	{
	case TYPE_NORMAL:			
	case TYPE_PUSH:
		{
			GnVerify( CreateNormalImage( pcDefaultImage ) );
			if( pcClickImage )
				GnVerify( CreateClickImage( pcClickImage ) );
			mMeshNames[TYPE_DISABLE] = pcDisableImage;
		}
		break;
	case TYPE_DISABLE:
		{
			GnVerify( CreateDisableImage( pcDisableImage ) );
			SetIsDisable( true );
			mMeshNames[TYPE_NORMAL] = pcDefaultImage;
			mMeshNames[TYPE_PUSH] = pcClickImage;
		}
		break;
	default:
		GnAssert( false );
	}
	mParentUseNode.retain();
}
GnIButton::~GnIButton()
{
	if( mpCoolTime )
		GnDelete mpCoolTime;
}

bool GnIButton::CreateNormalImage(const gchar* pcImageName)
{
	mpsNormalMesh = Gn2DMeshObject::CreateFromTextureFile( pcImageName );
	if( mpsNormalMesh == NULL )
		return  false;
	
	SetContentSize( mpsNormalMesh->GetSize().x, mpsNormalMesh->GetSize().y );
	AddMeshToParentNode( mpsNormalMesh );
	SetPosition( GetPosition() );
	return true;
}

bool GnIButton::CreateClickImage(const gchar* pcImageName)
{
	mpsPushMesh = Gn2DMeshObject::CreateFromTextureFile( pcImageName );
	if( mpsPushMesh == NULL )
		return  false;
	
	AddMeshToParentNode( mpsPushMesh );
	return true;
}

bool GnIButton::CreateDisableImage(const gchar* pcImageName)
{
	mpsDisableMesh = Gn2DMeshObject::CreateFromTextureFile( pcImageName );
	if( mpsDisableMesh == NULL )
		return  false;

	if( mpsNormalMesh == NULL )
		SetContentSize( mpsDisableMesh->GetSize().x, mpsDisableMesh->GetSize().y );
	
	AddMeshToParentNode( mpsDisableMesh );	
	SetPosition( GetPosition() );
	return true;
}

bool GnIButton::Push(float fPointX, float fPointY)
{
	if( GnInterface::Push(fPointX, fPointY) == false )
		return false;
	
//	if( mpsPushMesh )
//	{
//		mpsNormalMesh->SetVisible( false );
//		mpsPushMesh->SetVisible( true );
//	}
//	else
//		mpsNormalMesh->SetColor( GnColor( 0.0f, 1.0f, 0.0f ) );
	return true;
}
void GnIButton::Pushup(float fPointX, float fPointY)
{
	if( IsDisable() || IsCantPush() )
		return;

//	if( mpsPushMesh )
//	{
//		mpsNormalMesh->SetVisible( true );
//		mpsPushMesh->SetVisible( false );
//	}
//	else
//		mpsNormalMesh->SetColor( GnColor( 1.0f, 1.0f, 1.0f ) );
	
	GnInterface::Pushup(fPointX, fPointY);
}

void GnIButton::SetIsDisable(bool val)
{
	GnInterface::SetIsDisable( val );
	if( mpsDisableMesh == NULL )
	{
		if( mMeshNames[TYPE_DISABLE].Exists() == false )
			return;
		if( CreateDisableImage( mMeshNames[TYPE_DISABLE] ) == false )
			return;
	}
	GnAssert( mpsDisableMesh );
	
	SetVisibleNormal( !val );
	mpsDisableMesh->SetVisible( val );
}

void GnIButton::SetIsCantPush(bool val)
{
	GnInterface::SetIsCantPush( val );
	GnAssert( mpsNormalMesh || mpsDisableMesh );
	if( mpCoolTime == NULL && ( mpsNormalMesh || mpsDisableMesh ) )
	{
		Gn2DMeshObject* baseMesh = mpsNormalMesh ? mpsNormalMesh : mpsDisableMesh;
		GnVector2 size = baseMesh->GetSize();
		mpCoolTime = GnICoolTime::Create( size.x, size.y );
		GetParentUseNode()->addChild( mpCoolTime->GetParentUseNode(), 1 );
		mpCoolTime->SetPosition( GetPosition() );
	}
	GnAssert( mpCoolTime );
	if( mpCoolTime )
		mpCoolTime->SetVisibleBlind( val );
}

void GnIButton::AddMeshToParentNode(Gn2DMeshObject *pChild)
{
	GetParentUseNode()->addChild( pChild->GetMesh(), 0 );
}

void GnIButton::SetPosition(GnVector2& cPos)
{
	if( mpsNormalMesh )
		mpsNormalMesh->SetPosition( cPos );
	if( mpsPushMesh )
		mpsPushMesh->SetPosition( cPos );
	if( mpsDisableMesh )
		mpsDisableMesh->SetPosition( cPos );
	if( mpCoolTime )
		mpCoolTime->SetPosition( cPos);
}

void GnIButton::SetVisibleNormal(bool val)
{
	if( val )
	{
		if( mpsNormalMesh == NULL )
		{
			if( mMeshNames[TYPE_NORMAL].Exists() )
				CreateNormalImage( mMeshNames[TYPE_NORMAL] );
			if( mMeshNames[TYPE_PUSH].Exists() )
				CreateNormalImage( mMeshNames[TYPE_PUSH] );
		}
		
		GnAssert( mpsNormalMesh );
		if( mpsNormalMesh )
		{
			mpsNormalMesh->SetVisible( true );
			if( mpsPushMesh )
				mpsPushMesh->SetVisible( false );
		}
	}
	else
	{
		if( mpsNormalMesh )
		{
			mpsNormalMesh->SetVisible( false );
			if( mpsPushMesh )
				mpsPushMesh->SetVisible( false );
		}
	}
}