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

	pProp = new GcPropertyGridProperty(_T("Index"), 0L, _T("Index"));
	mpUseGridProperty[PROP_EXTRA_TYPE] = pProp;
	pProp->SetData( MSG_EXTRA_TYPE );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );	
	pGroup->AddSubItem( pProp );

	pProp = new GcPropertyGridProperty(_T("LInk ID"), 0L, _T("Link ID"));
	mpUseGridProperty[PROP_EXTRA_ID] = pProp;
	pProp->SetData( MSG_EXTRA_ID );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );	
	pGroup->AddSubItem( pProp );

	mpPropExtraPositionGroup =  new GcPropertyGridNumberPair( _T("Extra Position")
		, 0, GINT_MAX, 0, GINT_MAX, 0, TRUE ) ;
	mpPropExtraPositionGroup->AllowEdit( false );
	pProp = new GtBoundedNumberSubProp( _T("Position X"), (COleVariant)0L, GINT_MIN, GINT_MAX
		, _T("Extra Position x") );
	mpUseGridProperty[PROP_EXTRA_POSITIONX] = pProp;
	//pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX  );
	pProp->SetData( MSG_EXTRA_POSITIONX );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	mpPropExtraPositionGroup->AddSubItem( pProp );
	pProp = new GtBoundedNumberSubProp( _T("Position Y"), (COleVariant)0L, GINT_MIN, GINT_MAX
		, _T("Extra Position y") );
	mpUseGridProperty[PROP_EXTRA_POSITIONY] = pProp;
	//pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_EXTRA_POSITIONY );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	mpPropExtraPositionGroup->AddSubItem( pProp );
	pGroup->AddSubItem( mpPropExtraPositionGroup );
	pGroup->Expand();
	
	mpPropExtraIntGroup= new GcPropertyGridProperty(_T("Extra Int"), 0L, _T("Extra Int"));
	mpPropExtraIntGroup->SetData( MSG_EXTRA_INT );
	mpPropExtraIntGroup->SubscribeToUpdateEvent( &mUpdateEventSlot );
	pGroup->AddSubItem( mpPropExtraIntGroup );
	mpUseGridProperty[PROP_EXTRA_INT] = mpPropExtraIntGroup;
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
	if( GnDynamicCast(GnVector2ExtraData, mCurrentModifyExtraData) )
		ParsePostion( mCurrentModifyExtraData );
	else if( GnDynamicCast(GnIntExtraData, mCurrentModifyExtraData) )
		ParseInt( mCurrentModifyExtraData );

	CString name = GetMakeExtraDataTypeName( mNumEditExtraData
		, GetExtraDataType( mCurrentModifyExtraData ) );
	mpProperty->SetName( name );
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
				extra->SetValueX( (float)GetIntValue( GetExtraPointXProp()->GetValue() ) );
		}
		break;
	case MSG_EXTRA_POSITIONY:
		{
			GnVector2ExtraData* extra = GnDynamicCast(GnVector2ExtraData, mCurrentModifyExtraData);
			GnAssert( extra );
			if( extra )
				extra->SetValueY( (float)GetIntValue( GetExtraPointYProp()->GetValue() ) );
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
	case MSG_EXTRA_TYPE:
		{
			GnAssert( mCurrentModifyExtraData );
			if( mCurrentModifyExtraData )
				mCurrentModifyExtraData->SetType( (guint32)GetIntValue( GetExtraTypeProp()->GetValue() ) );
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
	GetExtraPointXProp()->SetValue( (long)pos[0] );
	GetExtraPointYProp()->SetValue( (long)pos[1] );
	GetExtraIDProp()->SetValue( (long)extra->GetID() );
	GetExtraTypeProp()->SetValue( (long)extra->GetType() );
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
	GetExtraTypeProp()->SetValue( (long)extra->GetType() );
	mpPropExtraPositionGroup->Show( true );
	mpPropExtraPositionGroup->Show( false );
}