#include "GnGamePCH.h"
#include "GActionFollows.h"
#include "GnIProgressBar.h"
#include "GInfoBasic.h"
#include "GCurrentActorInfo.h"
#include "GFileList.h"

GActionFollows::GActionFollows(GActorController* pController) : GAction( pController )
{
	
}

GActionFollows::~GActionFollows()
{
	if( mpsFollowMesh )
		GetActorLayer()->RemoveChild( mpsFollowMesh );
}

bool GActionFollows::CreateFollow(GActionFollows::eFollowType uiFollowsType)
{
	if( uiFollowsType == eShadow )
	{
		mFollowExtraType = GExtraData::EXTRA_SHADOW_POSITION;
		gstring fullName;
		if( GetFileList()->GetFullEffectName( 11, fullName ) )
			mpsFollowMesh = Gn2DMeshObject::CreateFullPath( fullName.c_str(), true );
		else
			return false;
	}
	return true;
}

void GActionFollows::Update(float fTime)
{
	if( mpsFollowMesh )
		mpsFollowMesh->Update( fTime );
	SetFollowPosition();
}

void GActionFollows::AttachActionToController()
{
	if( mpsFollowMesh )
		GetActorLayer()->AddChild( mpsFollowMesh, 11 );
}

void GActionFollows::DetachActionToController()
{
	if( mpsFollowMesh )
		GetActorLayer()->RemoveChild( mpsFollowMesh );
}

void GActionFollows::SetFollowPosition()
{
	GnVector2ExtraData* posExtraData = (GnVector2ExtraData*)
	GetController()->GetMesh()->GetExtraDataFromType( mFollowExtraType );
	
	if( posExtraData == NULL )
		return;
	
	GnVector2 Pos = GetController()->GetMesh()->GetPosition() + posExtraData->GetValueVector2();
	if( mpsFollowMesh )
		mpsFollowMesh->SetPosition( Pos );
}
