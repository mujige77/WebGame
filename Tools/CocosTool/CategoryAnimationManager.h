#pragma once
class CategoryAnimationManager
{
	CMFCRibbonEdit* mpAniStartTime;
	CMFCRibbonEdit* mpAniEndTime;
	CMFCRibbonEdit* mpAniTimeSpin;
	CMFCRibbonSlider* mpAniTimeSlider;
public:
	CategoryAnimationManager(void);
	~CategoryAnimationManager(void);

	void Create(CMFCRibbonBar* wndRibbonBar);	


	inline CMFCRibbonEdit* GetAniEndTime() {
		return mpAniEndTime;
	}
	inline CMFCRibbonEdit* GetAniStartTime() {
		return mpAniStartTime;
	}
	inline CMFCRibbonEdit* GetAniTimeSpin() {
		return mpAniTimeSpin;
	}
	inline CMFCRibbonSlider* GetAniTimeSlider() {
		return mpAniTimeSlider;
	}
};

