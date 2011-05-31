#pragma once
#include "GcPropertyGridProperty.h"
#include "GcMediateObject.h"

#define GtDeclareEntity(className) \
	public: \
	static CString StaticClassName() { return _T(#className); } \
	virtual CString GetClassName() { return _T(#className); }

GnSmartPointer(GcPropertyEntity);

class CMFCPropertyGridProperty;
class GcPropertyEntity : public GnSmartObject, public GcMediateObject
{
public:
	struct EntityData
	{
		GtObject* mpObject;
	};
protected:
	CString mName;
	CMFCPropertyGridProperty* mpProperty;	
	GnTObjectArray<GcPropertyEntityPtr> mChildren;

public:
	GcPropertyEntity(void);
	virtual ~GcPropertyEntity(void);

	void AddChild(GcPropertyEntity* child);
	void RemoveChild(gtuint uiIndex);
	void RemoveAllSubItem();	
	// 그리드 컨트롤이 삭제 되면서 프로퍼티도 삭제하기 때문에 널을 넣어 줬다
	void SetNullProperty();

	virtual CString GetClassName() = 0;
	virtual bool Init() = 0;
	virtual bool ParseToEntity(EntityData* pData) { return true; };
	virtual bool ParseToObject(EntityData* pData)  { return true; };
	virtual void SetClearValues() {};
	virtual void ApplyObjectData(CMFCPropertyGridProperty* pChangeProp, EntityData* pData) {};

	inline GcPropertyEntity* GetChild(gtuint uiIndex) {
		return mChildren.GetAt( uiIndex );
	}	
	
	inline CMFCPropertyGridProperty*& GetProperty() {
		return mpProperty;
	}
	inline CString& GetName() {
		return mName;
	}
	inline void SetName(CString val) {
		mName = val;
	}
	int GetIntValue(const COleVariant& var);
	float GetFloatValue(const COleVariant& var);
};