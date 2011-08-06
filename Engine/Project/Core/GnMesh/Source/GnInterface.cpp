#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnInterface.h"

GnImplementRootRTTI(GnInterface);

GnInterface::GnInterface() : mPushCount( 0 )
{
	SetIsHover( false );
	SetIsCantPush( false );
	SetIsDisable( false );	
	SetIsEnablePushMove( false );
	mParentUseNode.retain();
}

GnInterface::GnInterface(const gchar* pcImageName) : mPushCount( 0 )
{
	SetIsHover( false );
	SetIsCantPush( false );
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
	if( IsPush() == false || IfUseCheckCollision( fPointX, fPointY ) == false )
		return false;
	
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