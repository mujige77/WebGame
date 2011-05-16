#pragma once
#include "gtpropertyentity.h"
#include "GtPropertyGridProperty.h"

class GtSequenceInfoPropEntity : public GtPropertyEntity
{
private:
	class MainPropertyGridProperty : public GtPropertyGridProperty
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

	GtDeclareEntity(GtSequenceInfoPropEntity);
public:
	GtSequenceInfoPropEntity(void);
	virtual ~GtSequenceInfoPropEntity(void);

	virtual bool Init();
	CString GetFileName();	
	CString GetCurrenctSequenceName();
	//기존 파일 저장 되어있던 데이터를 입력
	void SetNames(LPCTSTR ptcSequenceName, LPCTSTR ptcFileName);

	// pObject 정보를 프로퍼티에 입력
	virtual bool ParseToEntity(GtStreamObject* pObject);
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

