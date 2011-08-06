#ifndef Core_GSelectStageUILayer_h
#define Core_GSelectStageUILayer_h

#include "GnIListCtrl.h"
#include "GInterfaceLayer.h"

class GnIListPageCtrl;
class GSelectStageUILayer : public GInterfaceLayer
{
	enum
	{
		NUM_ROW = 3,
		NUM_COLUMN = 6,
		NUM_PAGE = 4,
	};
private:
	GnIListPageCtrl* mpListCtrl;
	GnInterfaceGroup* mpButtonGroup;
	
public:
	void CreateListCtrlItem(guint32 uiLastStage);
	
public:
	virtual GnInterfaceGroup* CreateInterface(gtuint uiIndex
		, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot);
	virtual void Update(float fTime);
	
protected:
	GnInterfaceGroup* CreateListCrl();
	GnIListCtrlItem* CreateListCtrlItem(guint32 uiStarCount, bool isEnable);
	GnInterfaceGroup* CreateSelectStageButtons();
};

#endif
