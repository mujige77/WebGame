#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnInterface.h"

GnInterface::GnInterface() : mPushCount( 0 )
{
	SetIsHover( false );
	SetIsCantPush( false );
	SetIsDisable( false );	
	SetIsEnablePushMove( false );
	mParentUseNode.retain();
}

bool GnInterface::Push(float fPointX, float fPointY)
{
	AddPushCount();
	return true;
}

void GnInterface::Pushup(float fPointX, float fPointY)
{
	SubPushCount();
}

bool GnInterface::PushMove(float fPointX, float fPointY)
{
	if( IfUseCheckCollision( fPointX, fPointY ) == false )
		return false;
	
	return true;
}

void GnInterface::AddMeshToParentNode(Gn2DMeshObject *pChild)
{
	GetParentUseNode()->addChild( pChild->GetMesh(), 0 );
}

void GnInterface::AddToParentNode(GnInterfaceNode* pNode)
{
	GetParentUseNode()->addChild( pNode, 0 );
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