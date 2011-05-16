#ifndef GnMessageDefine_H
#define GnMessageDefine_H

const static guint PropEntityMessage = 250;

enum
{
	GTMG_ONTIMER = WM_USER + WM_USER,
	GTMG_SELECTOBJECT,	
	GTMG_NEWOBJECT,
	GTMG_DELTEOBJECT,
	GTMG_SELECTSEQUENCE,
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

class GtMediateObject;
class GtObject;
class GtSequenceInfo;
struct GtMediateObjectMessage
{
	GtMediateObject* mpSender;	
};

struct GtObjectMessage : public GtMediateObjectMessage
{
	GtObject* mpObject;
};

struct GtSequenceMessage : public GtMediateObjectMessage
{
	GtSequenceInfo* mpSequenceInfo;
};
#endif // GnMessageDefine_H
