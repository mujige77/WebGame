#ifndef Core_GLoadButtonLabel_h
#define Core_GLoadButtonLabel_h

#include "GnInterface.h"
#include "GnINumberLabel.h"
class GLoadButtonLabel : public GnInterface
{
private:
	GnINumberLabel mLabelNumStage;
public:
	static GLoadButtonLabel* CreateLabel(gtuint uiNumButton, guint32 uiModeLevel, guint32 uiNumStage);
	
public:
	inline void SetNumStageUIPoint(float fPointX, float fPointY) {
		mLabelNumStage.SetUIPoint( fPointX, fPointY );
	}
	
private:
	void CreateLabelStage(guint32 uiNumStage);
	void SetPosition(gtuint uiNumButton, guint32 uiModeLevel);
};

#endif
