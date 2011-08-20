#pragma once
#include "PropTreeInfo.h"

class CPropTreeDlgInfo : public CPropTreeInfo, CDialog
{
public:
	// CPropTree class that this class belongs
	void SetPropOwner(CPropTree* pProp);
protected:
	CPropTree*		m_pProp;

public:
	CPropTreeDlgInfo(void);
	~CPropTreeDlgInfo(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};
