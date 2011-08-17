#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnInterface.h"

GnImplementRootRTTI(GnInterface);

GnInterface::GnInterface() : mPushCount( 0 ), mTegID( -1 )
{
	SetIsHover( false );
	SetIsCantPush( true );
	SetIsDisable( false );	
	SetIsEnablePushMove( false );
	mParentUseNode.retain();
}

GnInterface::GnInterface(const gchar* pcImageName) : mPushCount( 0 ), mTegID( -1 )
{
	SetIsHover( false );
	SetIsCantPush( true );
	SetIsDisable( false );	
	SetIsEnablePushMove( false );
	mParentUseNode.retain();
	CreateDefaultImage( pcImageName );
}

bool GnInterface::Push(float fPointX, float fPointY)
{
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
		return false;

	Push();
	return true;
}

bool GnInterface::PushUp(float fPointX, float fPointY)
{
	if( IsPush() == false )
		return false;
	
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
	{
		PushUp();
		return false;
	}
	PushUp();
	return true;
}

bool GnInterface::PushMove(float fPointX, float fPointY)
{
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
		return false;
	
	return true;
}

void GnInterface::Push()
{
	AddPushCount();
}

void GnInterface::PushUp()
{
	SubPushCount();
}

void GnInterface::AddMeshToParentNode(Gn2DMeshObject *pChild)
{
	GetParentUseNode()->addChild( pChild->GetMesh(), 0 );
}

void GnInterface::AddToParentNode(GnInterfaceNode* pNode)
{
	GetParentUseNode()->addChild( pNode, 0 );
}

void GnInterface::AddInterfaceToParentNode(GnInterface* pInterface)
{
	GetParentUseNode()->addChild( pInterface->GetParentUseNode(), 0 );
}

void GnInterface::AddMeshToParentNode(Gn2DMeshObject *pChild, gtint iZorder)
{
	GetParentUseNode()->addChild( pChild->GetMesh(), iZorder );
}

void GnInterface::AddToParentNode(GnInterfaceNode* pNode, gtint iZorder)
{
	GetParentUseNode()->addChild( pNode, iZorder );
}

void GnInterface::AddInterfaceToParentNode(GnInterface* pInterface, gtint iZorder)
{
	GetParentUseNode()->addChild( pInterface->GetParentUseNode(), iZorder );
}

bool GnInterface::CreateDefaultImage(const gchar* pcImageName)
{
	if( pcImageName == NULL )
		mpsDefaultMesh = Gn2DMeshObject::Create( false );
	else
		mpsDefaultMesh = Gn2DMeshObject::CreateFromTextureFile( pcImageName );
	
	if( mpsDefaultMesh == NULL )
		return  false;
	
	SetContentSize( mpsDefaultMesh->GetSize().x, mpsDefaultMesh->GetSize().y );
	AddMeshToParentNode( mpsDefaultMesh );
	SetPosition( GetPosition() );
	return true;
}