#pragma once
#include "GtProperties.h"
#include "GtMainProperties.h"
#include "CalendarBar.h"
#include "GtTemplateTasksPane.h"

class GtWindowCreater
{
	static GtWindowCreater* mInstance;
protected:
	GtProperties    mAniProperties;
	GtMainProperties mMainProp;
	
public:
	static GtWindowCreater* Create();
	static void Destroy();
	static GtWindowCreater* GetInstance();	

	GtWindowCreater(void);
	~GtWindowCreater(void);	

	bool CreateUsedWindows(CMDIFrameWndEx* pParent, BOOL bHiColorIcons);
	void SetDockingWindows(CMDIFrameWndEx* pParent);
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	
	inline GtMainProperties& GetMainProperties() {
		return mMainProp;
	}

	inline GtProperties& GetAniProperties() {
		return mAniProperties;
	}
};

#define GetWindowCreater GtWindowCreater::GetInstance

