#ifndef GNRENDERVIEW_H
#define GNRENDERVIEW_H

#include "GnRenderObjectArray.h"
#include "GnListManager.h"

class GNMAIN_ENTRY GnRenderView : public GnListManager<GnObjectForm, GnObjectFormPtr>
{
	GnDeclareFlags(guint8);
	enum flags
	{
		ACTIVE_MASK = 0x01,
	};

protected:	
	GnRenderObjectArray mCollactRenderObject;

public:
	GnRenderView();
	virtual ~GnRenderView();

	void Render();
	virtual void Update(float fTime);

	inline bool GetActive()
	{
		return GetBit(ACTIVE_MASK);
	}
	inline void SetActive(bool val)
	{
		SetBit(val, ACTIVE_MASK);
	}

protected:
	virtual void AddToPVGeometryArray(GnObjectForm* object);
};

GnSmartPointer(GnRenderView);

#endif // GNRENDERVIEW_H