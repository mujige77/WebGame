#pragma once
#include "afxext.h"
#include <map>
class GDesignFormView : public CFormView
{
public:
	typedef CRuntimeClass* (CreateRuntimeClassFunc)(void);
private:
	static std::map<gstring, CreateRuntimeClassFunc*> mCreateFuncs;

public:
	static void AddCreateFunc(gstring strName, GDesignFormView::CreateRuntimeClassFunc* pFucn);
	static GDesignFormView::CreateRuntimeClassFunc* GetCreateFormViewFunction(gstring strName);
public:
	GDesignFormView(UINT nIDTemplate);
	virtual ~GDesignFormView(void);

	virtual void Save(GnStream* pStream) = 0;
	virtual void Load(GnStream* pStream) = 0;
	virtual const gchar* GetName() = 0;
};

#define RegFormView(classname) \
	GDesignFormView::AddCreateFunc( classname::GetStaicName(), classname::CreateFormView )	