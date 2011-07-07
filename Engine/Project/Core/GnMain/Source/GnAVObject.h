#ifndef GNAVOBJECT_H
#define GNAVOBJECT_H
#include "GnObjectForm.h"

class GnTransform;
class GnNode;
class GNMAIN_ENTRY GnAVObject : public GnObjectForm
{
	GnDeclareRTTI;
protected:
	GnTransform* mpTransform;
	GnNode* mpParent;

public:
	GnAVObject(GnTransform* pTrans);
	virtual ~GnAVObject();
	
	void AttachParent(GnNode* val);

	virtual void Update(float fTime);

	inline void DetachParent() { mpParent = NULL; }
	inline GnNode* GetParent() const { return mpParent; }

protected:
	void RemoveTimeControllerTarget();	
};

GnSmartPointer(GnAVObject);

#endif // GNAVOBJECT_H