#pragma once

#define GtDeclareEntity(className) \
	public: \
	static CString StaticClassName() { return _T(#className); } \
	virtual CString GetClassName() { return _T(#className); }

GnSmartPointer(GtPropertyEntity);

class CMFCPropertyGridProperty;
class GtPropertyEntity : public GnSmartObject
{
protected:
	CMFCPropertyGridProperty* mpProperty;
	CString mName;

	GnTObjectArray<GtPropertyEntityPtr> mChildren;

public:
	GtPropertyEntity(void);
	virtual ~GtPropertyEntity(void);

	virtual void SetClearValues() {};
	virtual void ApplyObjectData(CMFCPropertyGridProperty* pChangeProp, GtObject* pCurrentObject) {};

	void AddChild(GtPropertyEntity* child);
	void RemoveChild(gtuint uiIndex);
	void RemoveAllSubItem();	
	// 그리드 컨트롤이 삭제 되면서 프로퍼티도 삭제하기 때문에 널을 넣어 줬다
	void SetNullProperty();

	inline GtPropertyEntity* GetChild(gtuint uiIndex) {
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
	
	virtual CString GetClassName() = 0;
	virtual bool Init() = 0;
	virtual bool ParseToEntity(GtStreamObject* pObject) = 0;
	virtual bool ParseToObject(GtObject* pObject) = 0;
};