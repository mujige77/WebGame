#pragma once
class GtPropertyGridProperty  : public CMFCPropertyGridProperty
{
protected:
	bool mEnableGroupButton;
	int mGroupButtonWidth;
	CString mButtonName;

public:
	GtPropertyGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	GtPropertyGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);
	virtual ~GtPropertyGridProperty(void);
	
	// 기본값을 셋팅한다.
	void SetDefaultValue();
	void SetEnableGroupButton(bool val, LPCTSTR pcName = NULL);

	// 버튼 클릭 안되는 것 때문에 상속 받았음
	virtual BOOL OnEdit(LPPOINT lptClick);
	// 에디트 박스 더블클릭하면 들어 오는 곳임 에디트 박스 들어가게되면 다시 만들어 야됨
	virtual BOOL OnDblClk(CPoint point);
	// 텍스트 편집 부분에서 커서 바뀌는거 안바뀌게 할려고 오버라이드
	virtual BOOL OnSetCursor() const;	
	void AdjustButtonRect();

	// 파일 다이얼로그를 열기위한 버튼을 그린다
	void DrawButton(CDC* pDC);
	// 파일 선택하기 버튼쪽에 마우스포인트가 있는지 확인
	// (루트 일때 더블 클릭하면 확장 또는 숨기기가 되는데 그것을 막기위해 만듬)
	bool ButtonHitTest(CPoint point);

	inline bool GetEnableGroupButton() {
		return mEnableGroupButton;
	}	
	inline int GetGroupButtonWidth() {
		return mGroupButtonWidth;
	}
	inline void SetGroupButtonWidth(int val) {
		mGroupButtonWidth = val;
	}
};

