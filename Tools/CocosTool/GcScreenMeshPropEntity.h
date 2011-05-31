#ifndef GTSCREENMESHPROPENTITY_H
#define GTSCREENMESHPROPENTITY_H

#pragma once
#include "GcPropertyEntity.h"

class GcScreenMeshPropEntity : public GcPropertyEntity
{
	GtDeclareEntity(GcScreenMeshPropEntity);
public:
	enum
	{
		PROP_FILENAME,
		PROP_PAIRSIZE,
		PROP_HEIGHT = 0,
		PROP_WIDTH,
	};

	enum eMessage
	{
		MSG_HEIGHT = 250,
		MSG_WIDTH,
	};
public:
	GcScreenMeshPropEntity(void);
	virtual ~GcScreenMeshPropEntity(void);

	virtual bool Init();

	virtual bool ParseToEntity(GtObject* pObject);
	virtual bool ParseToObject(GtObject* pObject);

	inline GcPropertyGridProperty* GetFileNameProp() {
		return (GcPropertyGridProperty*)mpProperty->GetSubItem(PROP_FILENAME);
	}
	inline GcPropertyGridProperty* GetHeightProp() {
		return (GcPropertyGridProperty*)mpProperty->GetSubItem(PROP_PAIRSIZE)->GetSubItem( PROP_HEIGHT );
	}
	inline GcPropertyGridProperty* GetWidthProp() {
		return (GcPropertyGridProperty*)mpProperty->GetSubItem(PROP_PAIRSIZE)->GetSubItem( PROP_WIDTH );
	}
}; 

#endif // GTSCREENMESHPROPENTITY_H
