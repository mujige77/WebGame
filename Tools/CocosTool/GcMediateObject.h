#pragma once
#include <map>
#include "CocosTool.h"

class GcMediateObject
{
protected:
	typedef std::multimap<gtuint, GcMediateObject*>::iterator MediateMapIter;
	static std::multimap<gtuint, GcMediateObject*> mMediate;

public:
	GcMediateObject(void);
	~GcMediateObject(void);
	bool GetIterFromMessageObjectInfo(gtuint messageIndex, GcMediateObject* pObject, MediateMapIter& outIter);	
	void SendMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage);
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage){};

protected:
	void AttachNeedMessage(gtuint messageIndex);
	void DetachNeedMessage(gtuint messageIndex);
};

