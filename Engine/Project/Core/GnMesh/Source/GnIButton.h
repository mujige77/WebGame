#ifndef __Core__GnIButton__
#define __Core__GnIButton__

class GnIProgressBar;
class GnIButton : public GnInterface
{
	GnDeclareRTTI;
	GnDeclareFlags(gushort);	
public:
	enum
	{
		MASK_DEABLE_CANTPUSH_BLIND = 0x0001,
		MASK_ENABLE_COOLTIME = 0x0002,
		MASK_HIDE_PUSHDEFAULTBUTTON = 0x0004,
		MASK_HIDE_PUSHUPCLICKBUTTON = 0x0008,
	};
public:
	enum eButtonType
	{
		TYPE_NORMAL,
		TYPE_PUSH,
		TYPE_DISABLE,
		TYPE_PROGRESSBACK,
		TYPE_PROGRESS,
		TYPE_MAX,
	};
	
protected:
	Gn2DMeshObjectPtr mpsPushMesh;
	Gn2DMeshObjectPtr mpsDisableMesh;
	GnIProgressBar* mpProgressTime;
	GnSimpleString mMeshNames[TYPE_MAX];
	
public:
	GnIButton(const gchar* pcDefaultImage, const gchar* pcClickImage = NULL
		, const gchar* pcDisableImage = NULL, eButtonType eDefaultType = TYPE_NORMAL);
	virtual ~GnIButton();
	bool CreateClickImage(const gchar* pcImageName);
	bool CreateDisableImage(const gchar* pcImageName);
	void SetCoolTime(float fTime);

public:
	virtual void Update(float fTime);
	virtual bool Push(float fPointX, float fPointY);
	virtual bool PushMove(float fPointX, float fPointY);
	virtual void Push();
	virtual void PushUp();
	virtual void SetIsDisable(bool val);
	virtual void SetIsCantPush(bool val);
	virtual void SetPosition(GnVector2& cPos);
	virtual void SetAlpha(guchar ucAlpha);
	virtual void SetVisibleNormal(bool val);
public:
	inline bool IsDisableCantpushBlind() {
		return GetBit( MASK_DEABLE_CANTPUSH_BLIND );
	}
	inline void SetIsDisableCantpushBlind(bool val) {
		return SetBit( val, MASK_DEABLE_CANTPUSH_BLIND );
	}
	inline bool IsEnableCoolTime() {
		return GetBit( MASK_ENABLE_COOLTIME );
	}
	inline void SetIsEnableCoolTime(bool val) {
		if( val && mpProgressTime == NULL )
			CreateProgressBar();
		return SetBit( val, MASK_ENABLE_COOLTIME );
	}
	inline void SetProgressBarFileName(const gchar* pcProgressBackFileName, const gchar* pcProgressFileName) {
		mMeshNames[TYPE_PROGRESSBACK] = pcProgressBackFileName;
		mMeshNames[TYPE_PROGRESS] = pcProgressFileName;
	}
	inline bool IsHidePushDefaultButton() {
		return GetBit( MASK_HIDE_PUSHDEFAULTBUTTON );
	}
	inline void SetIsHidePushDefaultButton(bool val) {
		return SetBit( val, MASK_HIDE_PUSHDEFAULTBUTTON );
	}
	inline bool IsHidePushUpClickButton() {
		return GetBit( MASK_HIDE_PUSHUPCLICKBUTTON );
	}
	inline void SetIsHidePushUpClickButton(bool val) {
		return SetBit( val, MASK_HIDE_PUSHUPCLICKBUTTON );
	}
	
protected:
	void CreateProgressBar();
};

#endif
