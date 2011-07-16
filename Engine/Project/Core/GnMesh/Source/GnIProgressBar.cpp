//
//  GnIProgressBar.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 15..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GnIProgressBar.h"

GnIProgressBar* GnIProgressBar::Create(eProgressType eType, const gchar* pcBackImageName
	, const gchar* pcProgressImagaeName)
{
	GnAssert( pcBackImageName || pcProgressImagaeName );
	
	Gn2DMeshObject* backMesh = NULL;
	if( pcBackImageName )
		backMesh = Gn2DMeshObject::Create( pcBackImageName );

	Gn2DMeshObject* progressMesh = NULL;
	if( pcProgressImagaeName )
		progressMesh = Gn2DMeshObject::Create( pcBackImageName );
	
	if( backMesh == NULL && progressMesh == NULL )
		return NULL;
	
	Gn2DMeshObject* tempMesh = NULL;
	GnVector2 tempSize;
	if( backMesh == NULL || progressMesh == NULL )
	{
		tempMesh = Gn2DMeshObject::Create( false );
		if( backMesh == NULL )
			tempSize = progressMesh->GetSize();
		else 
			tempSize = backMesh->GetSize();
	}

		
	if( tempMesh )
	{
		tempMesh = Gn2DMeshObject::Create( false );
		tempMesh->GetMesh()->setTextureRect( CCRectMake(0, 0, tempSize.x, tempSize.y) );
		tempMesh->SetColor( GnColor::Black );
		tempMesh->SetAlpha( 0.5f );	
	}
	
	GnIProgressBar* coolTime = GnNew GnIProgressBar( eType, backMesh, progressMesh );
	return coolTime;	
}

GnIProgressBar* GnIProgressBar::Create(eProgressType eType, float fWidth, float fHeight)
{
	Gn2DMeshObject* backMesh = Gn2DMeshObject::Create( false );
    backMesh->GetMesh()->setTextureRect( CCRectMake(0, 0, fWidth, fHeight) );
    backMesh->SetColor( GnColor::Black );
	backMesh->SetAlpha( 0.5f );
	
    Gn2DMeshObject* progressMesh = Gn2DMeshObject::Create( false );
    progressMesh->GetMesh()->setTextureRect( CCRectMake(0, 0, fWidth, fHeight) );
    progressMesh->SetColor( GnColor::Black );
	progressMesh->SetAlpha( 0.5f );
	
	GnIProgressBar* coolTime = GnNew GnIProgressBar( eType, backMesh, progressMesh );
	return coolTime;
}

GnIProgressBar::GnIProgressBar(eProgressType eType, Gn2DMeshObject* pBackMesh, Gn2DMeshObject* pProgress)
	: mAcumtime(0.0f), mProgressType( eType )
	, mProgressTime( 0.0f ), mPlayPlag( GnIProgressBar::STOP )
{
	GetParentUseNode()->addChild( pBackMesh->GetMesh(), 0);
	mpsDefaultMesh = pBackMesh;
	mpsDefaultMesh->SetVisible( false );
	
	GetParentUseNode()->addChild( pProgress->GetMesh(), 1 );
    mpsProgressMesh = pProgress;
	mpsProgressMesh->SetVisible( false );
	
	GnVector2 size = mpsProgressMesh->GetSize();	
	mProgressWidth = size.x;
	mProgressHeight = size.y;
}

void GnIProgressBar::SetProgressPercent(gtuint uiPercent)
{
	float size = (float)uiPercent / (float)100;
	switch( mProgressType )
	{
		case eHorizontalFromRight:
		{
			ProgressFromRight( size );
		}
		break;
		case eHorizontalFromLeft:
		{
			ProgressFromLeft( size );
		}
		break;
		case eVerticalFromTop:
		{
			ProgressFromTop( size );
		}
		break;
		case eVerticalFromBottom:
		{
			ProgressFromBottom( size );
		}
		break;	
	}
		
}

void GnIProgressBar::ProgressFromLeft(float fSize)
{
	float size = mProgressWidth - ( mProgressWidth * fSize );
	GnVector2 CurrentPos = mOriginalPosition;
	CurrentPos.x = mOriginalPosition.x + size;
	mpsProgressMesh->SetPosition( CurrentPos );
	mpsProgressMesh->GetMesh()->setScaleX( fSize );
}

void GnIProgressBar::ProgressFromRight(float fSize)
{
	float size = mProgressWidth - ( mProgressWidth * fSize );
	GnVector2 CurrentPos = mOriginalPosition;
	CurrentPos.x = mOriginalPosition.x - ( size / 2 );
	mpsProgressMesh->SetPosition( CurrentPos );
	mpsProgressMesh->GetMesh()->setScaleX( fSize );
}

void GnIProgressBar::ProgressFromTop(float fSize)
{
	float size = mProgressHeight - ( mProgressHeight * fSize );
	GnVector2 CurrentPos = mOriginalPosition;
	CurrentPos.y = mOriginalPosition.y - size;
	mpsProgressMesh->SetPosition( CurrentPos );
	mpsProgressMesh->GetMesh()->setScaleY(fSize);
}

void GnIProgressBar::ProgressFromBottom(float fSize)
{
	float size = mProgressHeight - ( mProgressHeight * fSize );
	GnVector2 CurrentPos = mOriginalPosition;
	CurrentPos.y = mOriginalPosition.y + ( size / 2 );
	mpsProgressMesh->SetPosition( CurrentPos );
	mpsProgressMesh->GetMesh()->setScaleY(fSize);
}

void GnIProgressBar::Update(float fDeltaTime)
{
	if( mPlayPlag == PLAY )
	{
		mAcumtime -= fDeltaTime;
		if( mAcumtime <= 0.0f )
		{
			mAcumtime = 0.0f;
			Stop();
		}
		SetProgressPercent( 100 * mAcumtime / mProgressTime );
	}
}

void GnIProgressBar::SetPosition(GnVector2& cPos)
{
	GnInterface::SetPosition( cPos );
	mpsProgressMesh->SetPosition( cPos );
	mOriginalPosition = cPos;
}