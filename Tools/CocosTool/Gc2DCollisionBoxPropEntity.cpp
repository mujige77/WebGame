#include "StdAfx.h"
#include "CocosTool.h"
#include "Gc2DCollisionBoxPropEntity.h"
#include "GcPropertyGridNumberPair.h"
#include "GcPropertyGridTwoButtonsProperty.h"

Gc2DCollisionBoxPropEntity::Gc2DCollisionBoxPropEntity(void)
{
	Init();
}


Gc2DCollisionBoxPropEntity::~Gc2DCollisionBoxPropEntity(void)
{
}

bool Gc2DCollisionBoxPropEntity::Init()
{
	mNumEditCollisionRect = -1;
	mUpdateEventSlot.Initialize( this, &Gc2DCollisionBoxPropEntity::UpdateEvent );

	GcPropertyGridProperty* pGroup = NULL;
	pGroup = new GcPropertyGridProperty(_T("Anchor Point info"));
	mpProperty = pGroup;

	GcPropertyGridProperty* pProp = NULL;
	std::auto_ptr<CMFCPropertyGridProperty> apSize( new GcPropertyGridNumberPair( _T("AnchorPoint")
		, 0, GINT_MAX, 0, GINT_MAX, 0, TRUE ) );
	apSize->AllowEdit( false );
	pProp = new GtBoundedNumberSubProp( _T("Position X"), (COleVariant)(float)0, GINT_MIN, GINT_MAX
		, _T("AnchorPoint Position x") );
	mpUseGridProperty[PROP_ANCHORPOINTX] = pProp;
	pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_ANCHORPOINTX );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apSize->AddSubItem( pProp );
	pProp = new GtBoundedNumberSubProp( _T("Position Y"), (COleVariant)(float)0, GINT_MIN, GINT_MAX
		, _T("AnchorPoint Position y") );
	mpUseGridProperty[PROP_ANCHORPOINTY] = pProp;
	pProp->EnableFloatSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_ANCHORPOINTY );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apSize->AddSubItem( pProp );
	pGroup->AddSubItem( apSize.release() );	

	pGroup = new GcPropertyGridProperty(_T("Collision Box info"));
	mpProperty2 = pGroup;

	std::auto_ptr<GcPropertyGridNumberPair> apSize2( new GcPropertyGridNumberPair(
		_T("Collision box Postion"), GINT_MIN, GINT_MAX, GINT_MIN, GINT_MAX, 0, TRUE) );
	apSize2->AllowEdit( false );
	pProp = new GtBoundedNumberSubProp( _T("Position X"), (COleVariant) 250l, GINT_MIN, GINT_MAX
		, _T("Position x") );
	mpUseGridProperty[PROP_RECT_POSITIONX] = pProp;
	pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_RECTPOSITIONX );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );	
	apSize2->AddSubItem( pProp );
	pProp = new GtBoundedNumberSubProp( _T("Position Y"), (COleVariant) 150l, GINT_MIN, GINT_MAX
		, _T("Position y") );
	mpUseGridProperty[PROP_RECT_POSITIONY] = pProp;
	pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_RECTPOSITIONY );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apSize2->AddSubItem( pProp );
	pGroup->AddSubItem( apSize2.release() );
	
	std::auto_ptr<GcPropertyGridNumberPair> apSize3(new GcPropertyGridNumberPair(_T("Collision box Size")
		, 0, GINT_MAX, 0, GINT_MAX, 0, TRUE));
	apSize3->AllowEdit( false );
	pProp = new GtBoundedNumberSubProp(_T("Width"), (COleVariant) 250l, GINT_MIN, GINT_MAX
		, _T("Width"));
	mpUseGridProperty[PROP_RECT_SIZEWIDTH] = pProp;
	pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_RECTWIDTH );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apSize3->AddSubItem( pProp );
	pProp = new GtBoundedNumberSubProp( _T("Height"), (COleVariant) 150l, GINT_MIN, GINT_MAX
		, _T("Height"));
	mpUseGridProperty[PROP_RECT_SIZEHEIGHT] = pProp;
	pProp->EnableSpinControl( TRUE, GINT_MIN, GINT_MAX );
	pProp->SetData( MSG_RECTHEIGHT );
	pProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	apSize3->AddSubItem( pProp );
	pGroup->AddSubItem( apSize3.release() );
	
	return true;
}

bool Gc2DCollisionBoxPropEntity::ParseToEntity(EntityData* pData)
{
	ThisEntityData* thisEntityData = (ThisEntityData*)pData;
	mp2DActor = (Gt2DActor*)thisEntityData->mpObject;
	mpSequenceObject = thisEntityData->mpSequenceObject;
	mNumEditCollisionRect = thisEntityData->mSelectRectIndex;

	Gn2DAVData* avData = Get2DAVData();
	if( avData == NULL )
		return false;
	
	GetAnchorPointXProp()->SetValue( (COleVariant)(float)avData->GetAnchorPoint().x );
	GetAnchorPointYProp()->SetValue( (COleVariant)(float)avData->GetAnchorPoint().y );

	if( mNumEditCollisionRect >= (int)avData->GetCollisionCount() )
		return false;

	Gn2DAVData::CollisionRect rect = avData->GetCollisionRect( mNumEditCollisionRect );
	GnAssert( rect.mType < Gg2DCollision::COLLISION_MAX );
	ParseCollisionRect(mNumEditCollisionRect, rect);
	

	return true;
}

void Gc2DCollisionBoxPropEntity::ApplyObjectData(CMFCPropertyGridProperty* pChangeProp
	, EntityData* pData)
{

}

void Gc2DCollisionBoxPropEntity::UpdateEvent(GcPropertyGridProperty* pChangedGridProperty)
{
	Gn2DAVData* avData = Get2DAVData();
	if( avData == NULL )
		return;

	switch( pChangedGridProperty->GetData() )
	{
	//case MSG_COLLISIONLIST:
	//	{
	//		mNumEditCollisionRect = -1;
	//		for( int i = 0 ; i < pChangedGridProperty->GetOptionCount() ; i++ )
	//		{
	//			Gn2DAVData::CollisionRect& rect = avData->GetCollisionRect( (gtuint)i );
	//			CString collisionName = GetCollisionListName( i, gsCollisionType[rect.mType] );
	//			CString optionName = pChangedGridProperty->GetOption( i );
	//			if( collisionName == optionName )
	//			{
	//				ParseCollisionRect( i, rect );
	//				break;
	//			}
	//		}
	//		GnAssert( mNumEditCollisionRect >= 0 );
	//	}
	//	break;
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
	case MSG_RECTPOSITIONX:
		{
			if( mNumEditCollisionRect < 0 )
				return;
			
			int val = GetIntValue( GetCollisionPostionXProp()->GetValue() );
			Gn2DAVData::CollisionRect& rect = avData->GetCollisionRect( (gtuint)mNumEditCollisionRect );
			rect.mRect.MoveX( val - rect.mRect.left );
			avData->SetCollisionRect( (gtuint)mNumEditCollisionRect, rect.mType, rect.mRect );
		}
		break;
	case MSG_RECTPOSITIONY:
		{
			if( mNumEditCollisionRect < 0 )
				return;

			int val = GetIntValue( GetCollisionPostionYProp()->GetValue() );
			Gn2DAVData::CollisionRect& rect = avData->GetCollisionRect( (gtuint)mNumEditCollisionRect );
			rect.mRect.MoveY( val - rect.mRect.top );
			avData->SetCollisionRect( (gtuint)mNumEditCollisionRect, rect.mType, rect.mRect );
		}
		break;
	case MSG_RECTWIDTH:
		{
			if( mNumEditCollisionRect < 0 )
				return;

			int val = GetIntValue( GetCollisionSizeWidthProp()->GetValue() );
			Gn2DAVData::CollisionRect& rect = avData->GetCollisionRect( (gtuint)mNumEditCollisionRect );
			rect.mRect.SetWidth( val );
			avData->SetCollisionRect( (gtuint)mNumEditCollisionRect, rect.mType, rect.mRect );
		}
		break;
	case MSG_RECTHEIGHT:
		{
			if( mNumEditCollisionRect < 0 )
				return;

			int val = GetIntValue( GetCollisionSizeHeightProp()->GetValue() );
			Gn2DAVData::CollisionRect& rect = avData->GetCollisionRect( (gtuint)mNumEditCollisionRect );
			rect.mRect.SetHeight( val );
			avData->SetCollisionRect( (gtuint)mNumEditCollisionRect, rect.mType, rect.mRect );
		}
		break;
	default:
		return;
	}	
	
	SendMediateMessage( GTMG_REDRAW, NULL );
	mpSequenceObject->SetModifed( true );
}

CString Gc2DCollisionBoxPropEntity::GetCollisionListName(int iIndex, const TCHAR* pcName)
{
	CString name = pcName;
	if( iIndex < 10 )
		name += "0";
	name.AppendFormat( _T("%d"), iIndex );
	return name;
}

Gn2DAVData* Gc2DCollisionBoxPropEntity::Get2DAVData()
{
	if( mpSequenceObject == NULL )
		return NULL;

	Gn2DSequence* gnSequence = mpSequenceObject->GetSequence();
	if( gnSequence == NULL )
		return NULL;

	return gnSequence->GetAVData();
}

void Gc2DCollisionBoxPropEntity::ParseCollisionRect(gtuint i, Gn2DAVData::CollisionRect &rect)
{
	mNumEditCollisionRect = i;
	GetCollisionPostionXProp()->SetValue( (COleVariant)(long)rect.mRect.left );
	GetCollisionPostionYProp()->SetValue( (COleVariant)(long)rect.mRect.top );
	GetCollisionSizeWidthProp()->SetValue( (COleVariant)(long)rect.mRect.GetWidth() );
	GetCollisionSizeHeightProp()->SetValue( (COleVariant)(long)rect.mRect.GetHeight() );
}