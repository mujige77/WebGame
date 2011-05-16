#ifndef GNRENDERSTEP_H
#define GNRENDERSTEP_H

#include "GnRenderView.h"
#include "GnListManager.h"

class GNMAIN_ENTRY GnRenderViewSet : public GnListManager<GnRenderView, GnRenderViewPtr>
{
	GnDeclareFlags(guint8);
	enum flags
	{
		ACTIVE_MASK = 0x01,
		KEEP_BG_MASK = 0x02,
		USE_RENDERER_BG_MASK = 0x04,
	};

protected:
	GnRenderTargetPtr mpsRenderTarget;	
	guint mClearMode;	
	GnColorA mBackgroundColor;

public:
	GnRenderViewSet();
	virtual ~GnRenderViewSet();

	inline bool GetActive()
	{
		return GetBit(ACTIVE_MASK);
	}
	inline void SetActive(bool val)
	{
		SetBit(val, ACTIVE_MASK);
	}
	inline bool GetUseRendererBackgroundColor()
	{
		return GetBit(USE_RENDERER_BG_MASK);
	}
	inline void SetUseRendererBackgroundColor(bool val)
	{
		SetBit(val, USE_RENDERER_BG_MASK);
	}
	inline bool GetKeepRendererBackgroundColor()
	{
		return GetBit(KEEP_BG_MASK);
	}
	inline void SetKeepRendererBackgroundColor(bool val)
	{
		SetBit(val, KEEP_BG_MASK);
	}
	inline void GetBackgroundColor(GnColorA& outVal) const
	{
		outVal = mBackgroundColor;
	}
	inline void SetBackgroundColor(GnColorA& val)
	{
		mBackgroundColor = val;
	}
	inline guint GetClearMode()
	{
		return mClearMode;
	}
	inline void SetClearMode(guint val)
	{
		mClearMode = val;
	}
	inline GnRenderTarget* GetRenderTarget() 
	{
		return mpsRenderTarget;
	}
	inline void SetRenderTarget(GnRenderTargetPtr val)
	{
		mpsRenderTarget = val;
 	}

	void Render();
	void Update(float fTime);

protected:
	void RenderView();
};

GnSmartPointer(GnRenderViewSet);

#endif // GNRENDERSTEP_H