#include "GnMeshPCH.h"
#include "GnInterfacePCH.h"
#include "GnICoolTime.h"

GnICoolTime* GnICoolTime::Create(float fWidth, float fHeight)
{
	Gn2DMeshObject* sprite = GnNew Gn2DMeshObject();
    sprite->GetMesh()->setTextureRect( CCRectMake(0, 0, fWidth, fHeight) );
    sprite->SetColor( GnColor::Black );
	sprite->SetAlpha( 0.5f );
	
    Gn2DMeshObject* coolTimeMesh = GnNew Gn2DMeshObject();
    coolTimeMesh->GetMesh()->setTextureRect( CCRectMake(0, 0, fWidth, fHeight) );
    coolTimeMesh->SetColor( GnColor::Black );
	coolTimeMesh->SetAlpha( 0.5f );
	
	GnICoolTime* coolTime = GnNew GnICoolTime( sprite, coolTimeMesh );
	return coolTime;
}

void GnICoolTime::Update(float fDeltaTime)
{
	
}

GnICoolTime::GnICoolTime(Gn2DMeshObject* pBlindMesh, Gn2DMeshObject* pCoolTimeMesh) : mCoolTime( 0.0f )
{
	GetParentUseNode()->addChild( pBlindMesh->GetMesh(), 0);
	mpsBlindMesh = pBlindMesh;
	mpsBlindMesh->SetVisible( false );
	
	GetParentUseNode()->addChild( pCoolTimeMesh->GetMesh(), 1 );
    mpsCoolTimeMesh = pCoolTimeMesh;
	mpsCoolTimeMesh->SetVisible( false );
}

void GnICoolTime::SetPosition( GnVector2& cPos )
{
	mpsBlindMesh->SetPosition( cPos );
	mpsCoolTimeMesh->SetPosition( cPos );
}