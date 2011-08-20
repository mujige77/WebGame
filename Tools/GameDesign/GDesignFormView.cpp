#include "StdAfx.h"
#include "GDesignFormView.h"
std::map<gstring, GDesignFormView::CreateRuntimeClassFunc*> GDesignFormView::mCreateFuncs;

GDesignFormView::GDesignFormView(UINT nIDTemplate) : CFormView( nIDTemplate )
{
}


GDesignFormView::~GDesignFormView(void)
{
}

void GDesignFormView::AddCreateFunc(gstring strName, GDesignFormView::CreateRuntimeClassFunc* pFucn)
{
	mCreateFuncs[strName] = pFucn;
}
GDesignFormView::CreateRuntimeClassFunc* GDesignFormView::GetCreateFormViewFunction(gstring strName)
{
	return mCreateFuncs[strName];
}