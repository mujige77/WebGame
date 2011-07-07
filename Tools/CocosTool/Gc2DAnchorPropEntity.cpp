#include "StdAfx.h"
#include "CocosTool.h"
#include "Gc2DAnchorPropEntity.h"
#include "GcPropertyGridNumberPair.h"
#include "GcPropertyGridTwoButtonsProperty.h"

Gc2DAnchorPropEntity::Gc2DAnchorPropEntity(void)
{
	Init();
}


Gc2DAnchorPropEntity::~Gc2DAnchorPropEntity(void)
{
}

bool Gc2DAnchorPropEntity::Init()
{
	mUpdateEventSlot.Initialize( this, &Gc2DAnchorPropEntity::UpdateEvent );

	GcPropertyGridProperty* pGroup = NULL;
	pGroup = new GcPropertyGridProperty(_T("Anchor info"));
	mpProperty = pGroup;

	GcPropertyGridProperty* pProp = NULL;
	std::auto_ptr<CMFCPropertyGridProperty> apSize( new GcPropertyGridNumberPair( _T("Anchor Point")
		, 0, GINT_MAX, 0, GINT_MAX, 0, TRUE ) );
	apSize->AllowEdit( false );
	pProp = new GtBoundedNumberSubProp( _T("Position X"), (COleVariant)(float)0, GINT_MIN, GINT_MAX
		//pProp = new GtBoundedNumberSubProp( _T("Position X"), (COleVariant)0l, GINT_MIN, GINT_MAX
		, _T("AnchorPoint Position x") );
	mpUseGridProperty[PROP_ANCHORPOINTX] = pProp;
	pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	//pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_ANCHORPOINTX );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apSize->AddSubItem( pProp );
	pProp = new GtBoundedNumberSubProp( _T("Position Y"), (COleVariant)(float)0, GINT_MIN, GINT_MAX
		//pProp = new GtBoundedNumberSubProp( _T("Position Y"), (COleVariant)0l, GINT_MIN, GINT_MAX
		, _T("AnchorPoint Position y") );
	mpUseGridProperty[PROP_ANCHORPOINTY] = pProp;
	pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	//pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_ANCHORPOINTY );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apSize->AddSubItem( pProp );
	pGroup->AddSubItem( apSize.release() );	

	std::auto_ptr<CMFCPropertyGridProperty> apCenter( new GcPropertyGridNumberPair( _T("Flip Center")
		, 0, GINT_MAX, 0, GINT_MAX, 0, TRUE ) );
	apCenter->AllowEdit( false );
	//pProp = new GtBoundedNumberSubProp( _T("Image X"), (COleVariant)(float)0, GINT_MIN, GINT_MAX
		pProp = new GtBoundedNumberSubProp( _T("Center X"), (COleVariant)0l, GINT_MIN, GINT_MAX
		, _T("AnchorPoint Position x") );
	mpUseGridProperty[PROP_IMAGECENTERX] = pProp;
	//pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_IMAGECENTERX );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apCenter->AddSubItem( pProp );
	//pProp = new GtBoundedNumberSubProp( _T("Image Y"), (COleVariant)(float)0, GINT_MIN, GINT_MAX
		pProp = new GtBoundedNumberSubProp( _T("Center Y"), (COleVariant)0l, GINT_MIN, GINT_MAX
		, _T("AnchorPoint Position y") );
	mpUseGridProperty[PROP_IMAGECENTERY] = pProp;
	//pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_IMAGECENTERY );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apCenter->AddSubItem( pProp );
	pGroup->AddSubItem( apCenter.release() );	
	return true;
}

bool Gc2DAnchorPropEntity::ParseToEntity(EntityData* pData)
{
	ThisEntityData* thisEntityData = (ThisEntityData*)pData;
	mp2DActor = (Gt2DActor*)thisEntityData->mpObject;
	mpSequenceObject = thisEntityData->mpSequenceObject;

	Gn2DAVData* avData = Get2DAVData();
	if( avData == NULL )
		return false;

	GetAnchorPointXProp()->SetValue( (COleVariant)(float)avData->GetAnchorPoint().x );
	GetAnchorPointYProp()->SetValue( (COleVariant)(float)avData->GetAnchorPoint().y );
	GetImageCenterXProp()->SetValue( (COleVariant)(long)avData->GetImageCenter().x );
	GetImageCenterYProp()->SetValue( (COleVariant)(long)avData->GetImageCenter().y );
	return true;
}

void Gc2DAnchorPropEntity::UpdateEvent(GcPropertyGridProperty* pChangedGridProperty)
{
	Gn2DAVData* avData = Get2DAVData();
	if( avData == NULL )
		return;

	switch( pChangedGridProperty->GetData() )
	{
	case MSG_ANCHORPOINTX:
		{
			GnVector2 point = avData->GetAnchorPoint();
			point.x = GetFloatValue( GetAnchorPointXProp()->GetValue() );
			avData->SetAnchorPoint( point );
			mp2DActor->GetActor()->StopAnimation();
			mp2DActor->GetActor()->SetTargetAnimation(  mpSequenceObject->GetSequence()->GetID() );
		}
		break;
	case MSG_ANCHORPOINTY:
		{
			GnVector2 point = avData->GetAnchorPoint();
			point.y = GetFloatValue( GetAnchorPointYProp()->GetValue() );
			avData->SetAnchorPoint( point );
			mp2DActor->GetActor()->StopAnimation();
			mp2DActor->GetActor()->SetTargetAnimation(  mpSequenceObject->GetSequence()->GetID() );
		}
		break;
	case MSG_IMAGECENTERX:
		{
			GnVector2 point = avData->GetImageCenter();
			point.x = (float)GetIntValue( GetImageCenterXProp()->GetValue() );
			avData->SetImageCenter( point );
			mp2DActor->GetActor()->StopAnimation();
			mp2DActor->GetActor()->SetTargetAnimation(  mpSequenceObject->GetSequence()->GetID() );
		}
		break;
	case MSG_IMAGECENTERY:
		{
			GnVector2 point = avData->GetImageCenter();
			point.y = (float)GetIntValue( GetImageCenterYProp()->GetValue() );
			avData->SetImageCenter( point );
			mp2DActor->GetActor()->StopAnimation();
			mp2DActor->GetActor()->SetTargetAnimation(  mpSequenceObject->GetSequence()->GetID() );
		}
		break;
	default:
		return;
	}

	SendMediateMessage( GTMG_REDRAW, NULL );
	mpSequenceObject->SetModifed( true );
}

Gn2DAVData* Gc2DAnchorPropEntity::Get2DAVData()
{
	if( mpSequenceObject == NULL )
		return NULL;

	Gn2DSequence* gnSequence = mpSequenceObject->GetSequence();
	if( gnSequence == NULL )
		return NULL;

	return gnSequence->GetAVData();
}