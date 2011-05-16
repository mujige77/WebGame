#ifndef GTSCREENMESHPROPENTITY_H
#define GTSCREENMESHPROPENTITY_H

#pragma once
#include "GtPropertyEntity.h"
#include "GnMessageDefine.h"

class GtScreenMeshPropEntity : public GtPropertyEntity
{
	GtDeclareEntity(GtScreenMeshPropEntity);
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
	GtScreenMeshPropEntity(void);
	virtual ~GtScreenMeshPropEntity(void);

	virtual bool Init();

	virtual bool ParseToEntity(GtStreamObject* pObject);
	virtual bool ParseToObject(GtObject* pObject);

	inline GtPropertyGridProperty* GetFileNameProp() {
		return (GtPropertyGridProperty*)mpProperty->GetSubItem(PROP_FILENAME);
	}
	inline GtPropertyGridProperty* GetHeightProp() {
		return (GtPropertyGridProperty*)mpProperty->GetSubItem(PROP_PAIRSIZE)->GetSubItem( PROP_HEIGHT );
	}
	inline GtPropertyGridProperty* GetWidthProp() {
		return (GtPropertyGridProperty*)mpProperty->GetSubItem(PROP_PAIRSIZE)->GetSubItem( PROP_WIDTH );
	}
}; 

#endif // GTSCREENMESHPROPENTITY_H
