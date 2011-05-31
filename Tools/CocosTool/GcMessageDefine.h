#ifndef GNMESSAGEDEFINE_H
#define GNMESSAGEDEFINE_H

const static guint PropEntityMessage = 350;

enum
{
	GTMG_ONTIMER = WM_USER + WM_USER,
	GTMG_SELECTOBJECT,	
	GTMG_NEWOBJECT,
	GTMG_DELTEOBJECT,
	GTMG_SELECTSEQUENCE,
	GTMG_REDRAW,
	GTMG_DESTORY,
	GTMG_TIMECHANGE,
	GTMG_CHAGESEQUENCEANITIME,
	GTMG_CHECKENABLE_OKBUTTON,
	GTMG_VSLISTITEM_SELECTCHANGED,
	GTMG_VSLISTITEM_BEFOREREMOVE,
	GTMG_VSLISTITEM_AFTERADD,
	GTMG_VSLISTITEM_AFTERRENAME,
	GTMG_VSLISTITEM_MOVEUP,
	GTMG_VSLISTITEM_MOVEDOWN,
};

typedef struct tagGTVSITEMACTIVATE
{
	NMHDR hdr;
	HWND hwndListCtrl;
	int     iItem;
} GTVSITEMACTIVATE ;

class GcMediateObject;
class GtObject;
struct GcMediateObjectMessage
{
	GcMediateObjectMessage() : mpSender(NULL), mTempMessage(NULL), mpObject(NULL)
	{}
	GcMediateObject* mpSender;
	void* mTempMessage;
	GtObject* mpObject;
};

struct GcObjectMessage : public GcMediateObjectMessage
{
};

struct GcSequenceMessage : public GcObjectMessage
{
	GnActorTool::SequenceInfo* mpSequenceInfo;
};
#endif // GNMESSAGEDEFINE_H
