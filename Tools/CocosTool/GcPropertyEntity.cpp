#include "StdAfx.h"
#include "GcPropertyEntity.h"
#include "GcCollectionEntities.h"

GcPropertyEntity::GcPropertyEntity(void): mpProperty(NULL)
{
}

GcPropertyEntity::~GcPropertyEntity(void)
{
	if( mpProperty )
		delete mpProperty;
}

void GcPropertyEntity::RemoveAllSubItem()
{
	while( mpProperty->GetSubItemsCount() )
	{
		CMFCPropertyGridProperty* prop = mpProperty->GetSubItem(0);
		mpProperty->RemoveSubItem(prop, TRUE);
	}
}

int GcPropertyEntity::GetIntValue(const COleVariant& var)
{
	switch( var.vt )
	{
	case VT_I4:
	case VT_INT:
		return (int)var.lVal;
	case VT_I2:
		return (int)var.iVal;
	default:
		{
			GnAssert( 0 );
		}
	}
	return 0;
}
float GcPropertyEntity::GetFloatValue(const COleVariant& var)
{
	switch( var.vt )
	{
	case VT_R4:
		return var.fltVal;
	case VT_R8:
		return (float)var.dblVal;
	default:
		{
			GnAssert( 0 );
		}	
	}
	return 0.0f;
}

void GcPropertyEntity::AddChild(GcPropertyEntity* child)
{
	mpProperty->AddSubItem( child->GetProperty()  );
	mChildren.Add( child );
}

void GcPropertyEntity::RemoveChild(gtuint uiIndex)
{
	GcPropertyEntity* entity = mChildren.GetAt( uiIndex );
	mpProperty->RemoveSubItem( entity->GetProperty() );
	mChildren.RemoveAtAndFillAll( uiIndex );
}

void GcPropertyEntity::SetNullProperty()
{
	mpProperty = NULL;
	for( gtuint i = 0 ; i <  mChildren.GetSize() ; i++ )
	{
		GcPropertyEntity* pEntity = mChildren.GetAt( i );
		pEntity->SetNullProperty();
	}
}