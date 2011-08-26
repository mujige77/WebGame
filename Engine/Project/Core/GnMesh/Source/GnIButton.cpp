#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnIButton.h"
#include "GnIProgressBar.h"

GnImplementRTTI(GnIButton, GnInterface);

GnIButton::GnIButton(const gchar* pcDefaultImage, const gchar* pcClickImage
	, const gchar* pcDisableImage, GnIButton::eButtonType eDefaultType)
	: mpProgressTime(NULL)
{
	SetIsEnableCoolTime( false );
	SetIsDisableCantpushBlind( true );
	SetIsHidePushDefaultButton( true );
	SetIsHidePushUpClickButton( true );
	switch( (gint)eDefaultType )
	{
	case TYPE_NORMAL:			
	case TYPE_PUSH:
		{
			if( pcDefaultImage == NULL )
				return;
			
			GnVerify( CreateDefaultImage( pcDefaultImage ) );
			if( pcClickImage )
			{
				GnVerify( CreateClickImage( pcClickImage ) );
				if( mpsPushMesh )
					mpsPushMesh->SetVisible( false );
			}
			if( pcDisableImage )
			{
				CreateDisableImage( pcDisableImage );
				if( mpsDisableMesh )
					mpsDisableMesh->SetVisible( false );
			}
		}
		break;
	case TYPE_DISABLE:
		{
			GnVerify( CreateDisableImage( pcDisableImage ) );
			SetIsDisable( true );
			if( pcDefaultImage )
			{
				CreateDefaultImage( pcDefaultImage );
				if( mpsDefaultMesh )
					mpsDefaultMesh->SetVisible( false );
			}
			if( pcClickImage )
			{
				CreateClickImage( pcClickImage );
				if( mpsPushMesh )
					mpsPushMesh->SetVisible( false );
			}
		}
		break;
	default:
		GnAssert( false );
	}
	SetIsCantPush( false );
}
GnIButton::~GnIButton()
{
	if( mpProgressTime )
		GnDelete mpProgressTime;
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

	if( mpsDefaultMesh == NULL )
		SetContentSize( mpsDisableMesh->GetSize().x, mpsDisableMesh->GetSize().y );
	
	AddMeshToParentNode( mpsDisableMesh );	
	SetPosition( GetPosition() );
	return true;
}

void GnIButton::SetCoolTime(float fTime)
{
	if( mpProgressTime == NULL )
		CreateProgressBar();
	mpProgressTime->SetProgressTime( fTime );
}

void GnIButton::Update(float fTime)
{
	if( mpProgressTime )
		mpProgressTime->Update( fTime );
}

bool GnIButton::Push(float fPointX, float fPointY)
{
	if( ( mpProgressTime && mpProgressTime->GetPlayPlag() == GnIProgressBar::PLAY ) || 
	   GnInterface::Push(fPointX, fPointY) == false )
	   return false;
	
	return true;
}

bool GnIButton::PushMove(float fPointX, float fPointY)
{
	return GnInterface::PushMove( fPointX, fPointY );
}

void GnIButton::Push()
{
	GnInterface::Push();
	if( IsEnableCoolTime() )
	{
		if( mpProgressTime )
			mpProgressTime->Start();
	}
	if( mpsPushMesh )
	{
		if( IsHidePushDefaultButton() )
			mpsDefaultMesh->SetVisible( false );
		mpsPushMesh->SetVisible( true );
	}
	//	else
	//		mpsDefaultMesh->SetColor( GnColor( 0.0f, 1.0f, 0.0f ) );
}
void GnIButton::PushUp()
{
	GnInterface::PushUp();
	if( IsPush() == false )
	{
	}
	if( IsHidePushUpClickButton() )
	{
		mpsDefaultMesh->SetVisible( true );
		if( mpsPushMesh )
			mpsPushMesh->SetVisible( false );
	}
}

void GnIButton::SetIsDisable(bool val)
{
	GnInterface::SetIsDisable( val );
	if( mpsDisableMesh == NULL )
		return;
	
	SetVisibleNormal( !val );
	mpsDisableMesh->SetVisible( val );
}

void GnIButton::SetIsCantPush(bool val)
{
	GnInterface::SetIsCantPush( val );
	
	if( IsDisableCantpushBlind() )
		return;
	
	if( mpProgressTime == NULL )
		CreateProgressBar();
	if( mpProgressTime )
		mpProgressTime->SetVisibleBackground( val );
}

void GnIButton::SetPosition(GnVector2& cPos)
{
	GnInterface::SetPosition( cPos );
	if( mpsPushMesh )
		mpsPushMesh->SetPosition( cPos );
	if( mpsDisableMesh )
		mpsDisableMesh->SetPosition( cPos );
	if( mpProgressTime )
		mpProgressTime->SetPosition( cPos);
}

void GnIButton::SetAlpha(guchar ucAlpha)
{
	GnInterface::SetAlpha( ucAlpha );
	if( mpsPushMesh )
		mpsPushMesh->SetAlpha( ucAlpha );
	if( mpsDisableMesh )
		mpsDisableMesh->SetAlpha( ucAlpha );
}

void GnIButton::SetVisibleNormal(bool val)
{
	if( val )
	{
		//		if( mpsDefaultMesh == NULL )
		//		{
		//			if( mMeshNames[TYPE_NORMAL].Exists() )
		//				CreateDefaultImage( mMeshNames[TYPE_NORMAL] );
		//			if( mMeshNames[TYPE_PUSH].Exists() )
		//				CreateClickImage( mMeshNames[TYPE_PUSH] );
		//		}
		
		if( mpsDefaultMesh )
		{
			mpsDefaultMesh->SetVisible( true );
			if( mpsPushMesh )
				mpsPushMesh->SetVisible( false );
		}
	}
	else
	{
		if( mpsDefaultMesh )
		{
			mpsDefaultMesh->SetVisible( false );
			if( mpsPushMesh )
				mpsPushMesh->SetVisible( false );
		}
	}
}

void GnIButton::CreateProgressBar()
{
	GnAssert( mpsDefaultMesh || mpsDisableMesh );
	GnAssert( mpProgressTime == NULL );
	if( ( mpsDefaultMesh || mpsDisableMesh ) )
	{
		Gn2DMeshObject* baseMesh = mpsDefaultMesh ? mpsDefaultMesh : mpsDisableMesh;
		GnVector2 size = baseMesh->GetSize();
		mpProgressTime = GnIProgressBar::Create( GnIProgressBar::eHorizontalFromLeft, size.x, size.y );
		GetParentUseNode()->addChild( mpProgressTime->GetParentUseNode(), 1 );
		mpProgressTime->SetPosition( GetPosition() );
	}
}