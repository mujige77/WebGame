#pragma once
#include "GcPropertyEntity.h"

class GcBasicPropEntity : public GcPropertyEntity
{
public:
	enum eMessage
	{
		MSG_OBJECTNAME,
		MSG_OBJECTTYPE,
		MSG_FILENAME,	
		MSG_OBJECTINDEX,
	};

	enum
	{
		BASIC_OBJECTNAME,
		BASIC_OBJECTTYPE,
		BASIC_FILENAME,
		BASIC_INDEX,
	};

	GtDeclareEntity(GcBasicPropEntity);
public:
	GcBasicPropEntity();
	virtual ~GcBasicPropEntity(void);
	virtual bool Init();

	CString GetObjectName();
	CString GetObjectFileName();
	gtint GetObjectIndex();

	CMFCPropertyGridProperty* GetNameProp() {
		return mpProperty->GetSubItem( BASIC_OBJECTNAME );
	}
	CMFCPropertyGridProperty* GetTypeProp() {
		return mpProperty->GetSubItem( BASIC_OBJECTTYPE );
	}
	CMFCPropertyGridProperty* GetFileNameProp() {
		return mpProperty->GetSubItem( BASIC_FILENAME );
	}
	CMFCPropertyGridProperty* GetIndexProp() {
		return mpProperty->GetSubItem( MSG_OBJECTINDEX );
	}

	virtual bool ParseToEntity(GtObject* pObject);
	virtual bool ParseToObject(GtObject* pObject);

protected:
	void SetObjectType(GtObject* pObject);
	void SetObjectFileName(GtObject* pObject);
};

