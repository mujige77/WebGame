//
//  GnITabCtrl.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 22..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GnITabCtrl.h"
#include "GnITabPage.h"
#include "GnITabButton.h"

GnITabCtrl* GnITabCtrl::CreateTabCtrl(const gchar* pcBackgroundImage, float fSizeX, float fSizeY)
{
	Gn2DMeshObject* backgroundMesh = NULL;
	backgroundMesh = Gn2DMeshObject::CreateFromTextureFile( pcBackgroundImage );
	GnITabCtrl* tabCtrl = GnNew GnITabCtrl( backgroundMesh );
	GnVector2 size = backgroundMesh->GetSize();
	tabCtrl->SetContentSize( size.x, size.y );
	tabCtrl->mDefaultButtonSize = GnVector2( fSizeX, fSizeY );
	return tabCtrl;
}

GnITabCtrl* GnITabCtrl::CreateTabCtrl(float fTabBackgroundSizeX, float fTabBackgroundSizeY
	, float fTabButtonSizeX, float fTabButtonSizeY)
{
	GnITabCtrl* tabCtrl = GnNew GnITabCtrl( NULL );
	tabCtrl->SetContentSize( fTabBackgroundSizeX, fTabBackgroundSizeY );
	tabCtrl->mDefaultButtonSize = GnVector2( fTabButtonSizeX, fTabButtonSizeY );
	return tabCtrl;	
}
GnITabCtrl::GnITabCtrl(Gn2DMeshObject* pcBackgroundMesh) : mpTabButtons( NULL )
	, mTabButtonPushEvent( this, &GnITabCtrl::PushTabButton ), mNumActiveTab( -1 )
{
	mpTabButtons = GnNew GnInterfaceGroup();
	mpTabButtons->SubscribeClickedEvent( &mTabButtonPushEvent );	
	AddChild( mpTabButtons, INTERFACE_ZORDER + 1 );
	if( pcBackgroundMesh )
	{
		mpsDefaultMesh = pcBackgroundMesh;
		AddMeshToParentNode( pcBackgroundMesh, INTERFACE_ZORDER - 1 );
	}
}

void GnITabCtrl::AddTabCreateButtonImage(GnITabPage* pTabPage, const gchar* pcDefaultButtonImage
	, const gchar* pcClickButtonImage)
{
	GnAssert(pTabPage);
	pTabPage->SetIsVisible( false );
	pTabPage->SetNumTabPage( mpTabButtons->GetChildrenSize() );
	GnITabButton* button = GnNew GnITabButton( pTabPage, pcDefaultButtonImage, pcClickButtonImage );
	
	mpTabButtons->AddChild( button, INTERFACE_ZORDER +1 );
	mTabPages.Add( pTabPage );
	AddChild( pTabPage, INTERFACE_ZORDER - 1 );
	pTabPage->SetPosition( GetPosition() );
	pTabPage->SetRect( GetRect() );
	SetTabButtonPosition( GetStartTabButtonPosition() );
	
	for ( gtuint i = 0; i < mSignalSet.GetSize(); i++ )
	{
		pTabPage->SubscribeClickedEvent( mSignalSet.GetAt( i ) );
	}
}

void GnITabCtrl::SetActiveTab(gtint iNumActive)
{
	if( iNumActive != mNumActiveTab )
	{
		if( mNumActiveTab != -1 && mNumActiveTab < mpTabButtons->GetChildrenSize() )
		{
			GnInterface* child = mpTabButtons->GetChild( mNumActiveTab );
			if( child )
				child->PushUp();
		}
		if( iNumActive < mpTabButtons->GetChildrenSize() )
		{
			GnInterface* child = mpTabButtons->GetChild( iNumActive );
			if( child )
				child->Push();
		}
		mNumActiveTab = iNumActive;
	}
	
}

void GnITabCtrl::SetPosition(GnVector2& cPos)
{
	if( GetDefaultMesh() == NULL )
	{
		for ( gtuint i = 0; i < GetChildrenSize(); i++ )
		{
			GnITabPage* tabPage = GnDynamicCast( GnITabPage, GetChild( i ) );
			if( tabPage )
				tabPage->SetPosition( cPos );
		}
	}
	GnInterface::SetPosition( cPos );
	SetTabButtonPosition( GetStartTabButtonPosition() );
}

void GnITabCtrl::SetRect(float fLeft, float fTop, float fRight, float fBottom)
{
	GnInterfaceGroup::SetRect( fLeft, fTop, fRight, fBottom );
	mpTabButtons->SetRect( GetRect() );
	for ( gtuint i = 0; i < GetChildrenSize(); i++ )
	{
		GnITabPage* tabPage = GnDynamicCast( GnITabPage, GetChild( i ) );
		if( tabPage )
			tabPage->SetRect( GetRect() );
	}
}

void GnITabCtrl::SubscribeClickedEvent(GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot)
{
	mSignalSet.Add( pSlot );
	for ( gtuint i = 0; i < mTabPages.GetSize() ; i++ )
	{
		mTabPages.GetAt( i )->SubscribeClickedEvent( pSlot );
	}
}

GnVector2 GnITabCtrl::GetStartTabButtonPosition()
{
	GnVector2 backSize = GetContentSize();
	GnVector2 tabPos = GetPosition();
	backSize *= 0.5f;
	tabPos.x = tabPos.x - backSize.x + mDefaultButtonSize.x;
	tabPos.y += ( backSize.y + ( mDefaultButtonSize.y ) );
	return tabPos;
}

void GnITabCtrl::SetTabButtonPosition(GnVector2 cStartPos)
{
	for( gtuint i = 0; i < mpTabButtons->GetChildrenSize(); i++ )
	{
		GnIButton* button = (GnIButton*)mpTabButtons->GetChild( i );
		GnVector2 size = button->GetContentSize();
		GnVector2 pos = size * 0.5f;
		pos += cStartPos;
		button->SetPosition( pos );
		pos = button->GetUIPoint();
		button->SetRect( pos.x, pos.y, pos.x + size.x, pos.y + size.y );
		cStartPos.x += size.x;
	}
}

void GnITabCtrl::PushTabButton(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() != GnIInputEvent::PUSH )
		return;
	
	gint numPushTabButton = -1;
	for( gtuint i = 0; i < mpTabButtons->GetChildrenSize(); i++ )
	{
		GnInterface* child = mpTabButtons->GetChild( i );
		if( child == pInterface )
		{
			numPushTabButton = (gint)i;
		}
	}
	if( numPushTabButton == -1 )
		return;
	
	SetActiveTab( numPushTabButton );
}