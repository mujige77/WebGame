#include "StdAfx.h"
#include "CocosTool.h"
#include "GcExtraDataPropEntity.h"
#include "GcPropertyGridNumberPair.h"
#include "GcPropertyGridTwoButtonsProperty.h"

GcExtraDataPropEntity::GcExtraDataPropEntity(void)
{
	Init();
}


GcExtraDataPropEntity::~GcExtraDataPropEntity(void)
{
}

bool GcExtraDataPropEntity::Init()
{
	mUpdateEventSlot.Initialize( this, &GcExtraDataPropEntity::UpdateEvent );

	GcPropertyGridProperty* pGroup = NULL;
	pGroup = new GcPropertyGridProperty(_T("Extra Data"));
	mpProperty = pGroup;

	GcPropertyGridProperty* pProp = NULL;

	pProp = new GcPropertyGridProperty(_T("ID"), 0L, _T("ID"));
	mpUseGridProperty[PROP_EXTRA_ID] = pProp;
	pProp->SetData( MSG_EXTRA_ID );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );	
	pGroup->AddSubItem( pProp );

	mpPropExtraPositionGroup =  new GcPropertyGridNumberPair( _T("Extra Position")
		, 0, GINT_MAX, 0, GINT_MAX, 0, TRUE ) ;
	mpPropExtraPositionGroup->AllowEdit( false );
	pProp = new GtBoundedNumberSubProp( _T("Position X"), (COleVariant)(float)0, GINT_MIN, GINT_MAX
		, _T("Extra Position x") );
	mpUseGridProperty[PROP_EXTRA_POSITIONX] = pProp;
	pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_EXTRA_POSITIONX );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	mpPropExtraPositionGroup->AddSubItem( pProp );
	pProp = new GtBoundedNumberSubProp( _T("Position Y"), (COleVariant)(float)0, GINT_MIN, GINT_MAX
		, _T("Extra Position y") );
	mpUseGridProperty[PROP_EXTRA_POSITIONY] = pProp;
	pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	//pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_EXTRA_POSITIONY );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	mpPropExtraPositionGroup->AddSubItem( pProp );
	pGroup->AddSubItem( mpPropExtraPositionGroup );

	
	mpPropExtraIntGroup= new GcPropertyGridProperty(_T("Extra Int"), 0L, _T("Extra Int"));
	mpPropExtraIntGroup->SetData( MSG_EXTRA_INT );
	mpPropExtraIntGroup->SubscribeToUpdateEvent( &mUpdateEventSlot );
	pGroup->AddSubItem( mpPropExtraIntGroup );
	mpUseGridProperty[PROP_EXTRA_INT] = pProp;
	return true;
}

bool GcExtraDataPropEntity::ParseToEntity(EntityData* pData)
{
	ThisEntityData* thisEntityData = (ThisEntityData*)pData;
	mCurrentModifyExtraData = NULL;
	mpObject = thisEntityData->mpObject;
	mNumEditExtraData = thisEntityData->mSelectRectIndex;
	mpMeshObject = thisEntityData->mpMeshObject;
	if( mpMeshObject == NULL )
		return false;

	mCurrentModifyExtraData = mpMeshObject->GetExtraData( mNumEditExtraData );
	if( mCurrentModifyExtraData->GetType() == GExtraData::EXTRA_EFFECT_POSITION )
	{
		ParsePostion( mCurrentModifyExtraData );
	}
	else if( mCurrentModifyExtraData->GetType() == GExtraData::EXTRA_EFFECT )
	{
		ParseInt( mCurrentModifyExtraData );
	}
	return true;
}

void GcExtraDataPropEntity::UpdateEvent(GcPropertyGridProperty* pChangedGridProperty)
{
	switch( pChangedGridProperty->GetData() )
	{
	case MSG_EXTRA_POSITIONX:
		{
			GnVector2ExtraData* extra = GnDynamicCast(GnVector2ExtraData, mCurrentModifyExtraData);
			GnAssert( extra );
			if( extra )
				extra->SetValueX( GetFloatValue( GetExtraPointXProp()->GetValue() ) );
		}
		break;
	case MSG_EXTRA_POSITIONY:
		{
			GnVector2ExtraData* extra = GnDynamicCast(GnVector2ExtraData, mCurrentModifyExtraData);
			GnAssert( extra );
			if( extra )
				extra->SetValueY( GetFloatValue( GetExtraPointYProp()->GetValue() ) );
		}
		break;
	case MSG_EXTRA_INT:
		{
			GnIntExtraData* extra = GnDynamicCast(GnIntExtraData, mCurrentModifyExtraData);
			GnAssert( extra );
			if( extra )
				extra ->SetID( GetIntValue( GetExtraIntProp()->GetValue() ) );
		}
		break;
	case MSG_EXTRA_ID:
		{
			GnAssert( mCurrentModifyExtraData );
			if( mCurrentModifyExtraData )
				mCurrentModifyExtraData->SetID( (guint32)GetIntValue( GetExtraIDProp()->GetValue() ) );
		}
		break;
	default:
		return;
	}

	SendMediateMessage( GTMG_REDRAW, NULL );
	mpObject->SetModifed( true );
}

void GcExtraDataPropEntity::ParsePostion(GnExtraData* pExtra)
{
	GnVector2ExtraData* extra = GnDynamicCast(GnVector2ExtraData, pExtra);
	GnAssert( extra );
	if( extra == NULL )
		return;

	float* pos = extra->GetValue();
	GetExtraPointXProp()->SetValue( pos[0] );
	GetExtraPointYProp()->SetValue( pos[1] );
	GetExtraIDProp()->SetValue( (long)extra->GetID() );

	mpPropExtraPositionGroup->Show( true );
	mpPropExtraIntGroup->Show( false );
}

void GcExtraDataPropEntity::ParseInt(GnExtraData* pExtra)
{
	GnIntExtraData* extra = GnDynamicCast(GnIntExtraData, pExtra);
	GnAssert( extra );
	if( extra == NULL )
		return;

	GetExtraIntProp()->SetValue( (long)extra->GetValue() );
	GetExtraIDProp()->SetValue( (long)extra->GetID() );

	mpPropExtraPositionGroup->Show( true );
	mpPropExtraPositionGroup->Show( false );
}