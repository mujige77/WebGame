#pragma once
#include <map>
#include "GnMessageDefine.h"

class GtMediateObject
{
protected:
	typedef std::multimap<gtuint, GtMediateObject*>::iterator MediateMapIter;
	static std::multimap<gtuint, GtMediateObject*> mMediate;

public:
	GtMediateObject(void);
	~GtMediateObject(void);
	bool GetIterFromMessageObjectInfo(gtuint messageIndex, GtMediateObject* pObject, MediateMapIter& outIter);	
	void SendMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pSanderInfo);
	virtual void ReceiveMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pSanderInfo){};

protected:
	void AttachNeedMessage(gtuint messageIndex);		
};

