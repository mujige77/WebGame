#include "GnGamePCH.h"
#include "GCastle.h"
#include "GnIProgressBar.h"

GCastle::GCastle() : mpGageIcon( NULL ), mpCastleGage( NULL ), mpTopCastle( NULL )
	, mpBottomCastle( NULL ), mpTopDamageEffect( NULL ),  mpBottomDamageEffect( NULL )
	, mIsDamage( false ), mHP( 1000 ), mCurrentHP( 1000 ), mDamageEffectTime( 1.0f )
	, mDamageEffectAcumTime( 0.0f ), mAutoRecoveryHP( 5 )
{
	mAutoRecoveryHPTimer.SetPercentTime( 5 );
	mCastleStateFlag = eNormal;
}


void GCastle::Update(float fTime)
{
	if( mpsDeckEffect )
		mpsDeckEffect->Update( fTime );
	
	UpdateDamageEffect( fTime );
}

void GCastle::ReceveAttack(gint32 iDamage)
{
	if( mCastleStateFlag == eDestroy )
		return;
	
	mCurrentHP -= iDamage;
	if( GetCurrentHP() <= 0 )
	{
		mCastleStateFlag = eDestroy;
		SetCurrentState();
		return;
	}
	else if( GetCurrentHP() < GetHP() / 2 )
	{
		mCastleStateFlag = eBreak;
		SetCurrentState();
	}	
	GetCastleGege()->SetProgressPercent( (float)GetCurrentHP() / (float)GetHP() * 100.0f );
	
	if( mIsDamage == false )
	{
		mIsDamage = true;
		mpTopDamageEffect->SetVisible( true );
		mpBottomDamageEffect->SetVisible( true );
		GnTimeController::StartTimeControllers( mpTopDamageEffect );
		GnTimeController::StartTimeControllers( mpBottomDamageEffect );
	}
}

void GCastle::UpdateDamageEffect(float fTime)
{
	if( mIsDamage )
	{
		mDamageEffectAcumTime += fTime;
		if( mDamageEffectAcumTime >= mDamageEffectTime )
		{
			SetStopDamageEffect();
		}
		else
		{
			mpTopDamageEffect->Update( fTime );
			mpBottomDamageEffect->Update( fTime );
		}
	}
}

void GCastle::UpdateBreak(float fTime)
{
	
}


bool GCastle::CreateCastleData(GLayer* pCastleLayer, GStageInfo* pStageInfo, GStageInfo::GCastleFiles* pFiles
	  , GStageInfo::GCastlePositions* pPositions)
{
	float interfaceHeight = pStageInfo->GetInterfaceSize().y;
	float lineHeight = pStageInfo->GetLineHeight();
	float zOrder = GetGameState()->GetGameHeight() - interfaceHeight;
	// castle
	mpsCastleNormal = Gn2DMeshObject::CreateFromTextureFile( pFiles->mCastle );
	pCastleLayer->AddChild( mpsCastleNormal, zOrder - lineHeight );
	
	mpsCastleBreak = Gn2DMeshObject::CreateFromTextureFile( pFiles->mCastleBreak );
	pCastleLayer->AddChild( mpsCastleBreak, interfaceHeight );
	mpsCastleBreak->SetVisible( false );
	
	mpsCastleDestroy = Gn2DMeshObject::CreateFromTextureFile( pFiles->mCastleDestroy );
	pCastleLayer->AddChild( mpsCastleDestroy, zOrder - lineHeight );
	mpsCastleDestroy->SetVisible( false );
	
	mpsCastleBottom = Gn2DMeshObject::CreateFromTextureFile( pFiles->mCastleBottom );
	pCastleLayer->AddChild( mpsCastleBottom, zOrder );
	
	// effect
	mpsDamageEffectNormal = Gn2DMeshObject::Create( pFiles->mCastleDamageEffect, false );
	pCastleLayer->AddChild( mpsDamageEffectNormal, interfaceHeight );
	mpsDamageEffectNormal->SetVisible( false );
	
	mpsDamageEffectBreak = Gn2DMeshObject::Create( pFiles->mCastleBreakDamageEffect, false );
	pCastleLayer->AddChild( mpsDamageEffectBreak, interfaceHeight );
	mpsDamageEffectBreak->SetVisible( false );
	
	mpsDamageEffectBottom = Gn2DMeshObject::Create( pFiles->mCastleBottomDamageEffect, false );
	pCastleLayer->AddChild( mpsDamageEffectBottom, interfaceHeight );
	mpsDamageEffectBottom->SetVisible( false );
	
	if( pFiles->mDeckEffect.Exists() )
	{
		mpsDeckEffect = Gn2DMeshObject::Create( pFiles->mDeckEffect, false );
		pCastleLayer->AddChild( mpsDeckEffect, zOrder + 100 );
	}
	
	// castle
	GnVector2 pos = ConvertUIPositionToMeshPosition( mpsCastleNormal->GetSize(), pPositions->mCastle );
	mpsCastleNormal->SetPosition( pos );
	
	pos = ConvertUIPositionToMeshPosition( mpsCastleBreak->GetSize(), pPositions->mCastleBreak );
	mpsCastleBreak->SetPosition( pos );
	
	pos = ConvertUIPositionToMeshPosition( mpsCastleDestroy->GetSize(), pPositions->mCastleDestroy );
	mpsCastleDestroy->SetPosition( pos );
	
	pos = ConvertUIPositionToMeshPosition( mpsCastleBottom->GetSize(), pPositions->mCastleBottom );
	mpsCastleBottom->SetPosition( pos );
	
	// effect
	pos = ConvertUIPositionToMeshPosition( mpsDamageEffectNormal->GetSize(), pPositions->mCastleDamageEffect );
	mpsDamageEffectNormal->SetPosition( pos );
	
	pos = ConvertUIPositionToMeshPosition( mpsDamageEffectBreak->GetSize(), pPositions->mCastleBreakDamageEffect );
	mpsDamageEffectBreak->SetPosition( pos );	

	pos = ConvertUIPositionToMeshPosition( mpsDamageEffectBottom->GetSize(), pPositions->mCastleBottomDamageEffect );
	mpsDamageEffectBottom->SetPosition( pos );	
	
	if( mpsDeckEffect )
	{
		pos = ConvertUIPositionToMeshPosition( mpsDeckEffect->GetSize(), pPositions->mDeckEffect );
		mpsDeckEffect->SetPosition( pos );
		GnTimeController::SetCycleType( GnTimeController::LOOP, mpsDeckEffect );
		GnTimeController::StartTimeControllers( mpsDeckEffect );
	}
	
	SetCurrentState();
	return true;
}

void GCastle::SetCurrentState()
{
	GnVector2 position;
	
	SetStopDamageEffect();
	
	if( mpTopCastle )
		mpTopCastle->SetVisible( false );
	if( mpBottomCastle )
		mpBottomCastle->SetVisible( false );
	
	// change
	if( mCastleStateFlag == eNormal )
	{
		mpTopCastle = mpsCastleNormal;
		mpTopDamageEffect = mpsDamageEffectNormal;
		mTopBodyRect = GetRectFromCenterPosition( mpsCastleNormal->GetSize(), mpsCastleNormal->GetPosition() );
	}
	else if( mCastleStateFlag == eBreak )
	{
		mpTopCastle = mpsCastleBreak;	
		mpTopDamageEffect = mpsDamageEffectBreak;
		mTopBodyRect = GetRectFromCenterPosition( mpsCastleBreak->GetSize(), mpsCastleBreak->GetPosition() );
	}
	else
	{
		mIsDamage = false;
		mpsCastleDestroy->SetVisible( true );
		mpTopCastle = NULL;
		mpTopDamageEffect = NULL;
		mpBottomCastle = NULL;
		mpBottomDamageEffect = NULL;
		if( mpsDeckEffect )
			mpsDeckEffect->SetVisible( false );
		mpsDeckEffect = NULL;
		return;
	}
	mpBottomCastle = mpsCastleBottom;
	mpBottomDamageEffect = mpsDamageEffectBottom;
	mBottomBodyRect = GetRectFromCenterPosition( mpsCastleBottom->GetSize(), mpsCastleBottom->GetPosition() );
	
	mpTopCastle->SetVisible( true );
	mpBottomCastle->SetVisible( true );
	GnTimeController::StopTimeControllers( mpTopDamageEffect );
	GnTimeController::StopTimeControllers( mpBottomDamageEffect );
}


void GCastle::SetStopDamageEffect()
{
	if( mpTopDamageEffect )
	{
		mpTopDamageEffect->SetVisible( false );
		GnTimeController::StopTimeControllers( mpTopDamageEffect );
	}
	if( mpBottomDamageEffect )
	{
		mpTopDamageEffect->SetVisible( false );
		GnTimeController::StopTimeControllers( mpBottomDamageEffect );
	}	
	
	mIsDamage = false;
	mDamageEffectAcumTime = 0.0f;
}

void GCastle::UpdateHP(float fTime)
{
	if( mAutoRecoveryHPTimer.Update( fTime ) )
	{
		SetCurrentHP( GetCurrentHP() + GetAutoRecoveryHP() );
		mAutoRecoveryHPTimer.Reset();
	}
}