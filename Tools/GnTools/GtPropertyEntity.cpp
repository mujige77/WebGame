#include "StdAfx.h"
#include "GtPropertyEntity.h"
#include "GtCollectionEntities.h"

GtPropertyEntity::GtPropertyEntity(void): mpProperty(NULL)
{
}

GtPropertyEntity::~GtPropertyEntity(void)
{
	if( mpProperty )
		delete mpProperty;
}

void GtPropertyEntity::RemoveAllSubItem()
{
	while( mpProperty->GetSubItemsCount() )
	{
		CMFCPropertyGridProperty* prop = mpProperty->GetSubItem(0);
		mpProperty->RemoveSubItem(prop, TRUE);
	}
}

int GtPropertyEntity::GetIntValue(const COleVariant& var)
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
		return 0;
	}
}

void GtPropertyEntity::AddChild(GtPropertyEntity* child)
{
	mpProperty->AddSubItem( child->GetProperty()  );
	mChildren.Add( child );
}

void GtPropertyEntity::RemoveChild(gtuint uiIndex)
{
	GtPropertyEntity* entity = mChildren.GetAt( uiIndex );
	mpProperty->RemoveSubItem( entity->GetProperty() );
	mChildren.RemoveAtAndFillAll( uiIndex );
}

void GtPropertyEntity::SetNullProperty()
{
	mpProperty = NULL;
	for( gtuint i = 0 ; i <  mChildren.GetSize() ; i++ )
	{
		GtPropertyEntity* pEntity = mChildren.GetAt( i );
		pEntity->SetNullProperty();
	}
}