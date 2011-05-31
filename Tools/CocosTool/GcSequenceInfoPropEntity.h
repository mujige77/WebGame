#pragma once
#include "GcPropertyEntity.h"
#include "GcPropertyGridProperty.h"

class GcSequenceInfoPropEntity : public GcPropertyEntity
{
private:
	class MainPropertyGridProperty : public GcPropertyGridProperty
	{
	public:
		MainPropertyGridProperty(const CString& strName, const COleVariant& varValue);

	protected:
		virtual BOOL HasButton() const { return TRUE; }
		virtual void OnClickButton(CPoint point);
	};

public:
	enum eMessage
	{
		MSG_FILENAME = 50,
		MSG_SEQUENCEID,
	};

	GtDeclareEntity(GcSequenceInfoPropEntity);
public:
	GcSequenceInfoPropEntity(void);
	virtual ~GcSequenceInfoPropEntity(void);

	virtual bool Init();
	CString GetFileName();	
	CString GetCurrenctSequenceName();
	//기존 파일 저장 되어있던 데이터를 입력
	void SetNames(LPCTSTR ptcSequenceName, LPCTSTR ptcFileName);

	// pObject 정보를 프로퍼티에 입력
	virtual bool ParseToEntity(GtObject* pObject);
	// 프로퍼티 정보를 pObject에 입력
	virtual bool ParseToObject(GtObject* pObject);

protected:
	CMFCPropertyGridProperty* GetSequenceFileNameProp() {
		return mpProperty->GetSubItem(1);
	}

	CMFCPropertyGridProperty* GetSequenceNameProp() {
		return mpProperty->GetSubItem(0);
	}
};

