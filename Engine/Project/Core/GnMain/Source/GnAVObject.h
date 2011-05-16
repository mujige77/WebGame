#ifndef GNAVOBJECT_H
#define GNAVOBJECT_H
#include "GnObjectForm.h"
#include "GnTimeController.h"

class GnTransform;
class GnNode;
class GNMAIN_ENTRY GnAVObject : public GnObjectForm
{
	GnDeclareRTTI;
protected:
	GnTransform* mpTransform;
	GnNode* mpParent;
	GnTimeControllerPtr mspControls;

public:
	GnAVObject(GnTransform* pTrans);
	virtual ~GnAVObject();
	
	void AttachParent(GnNode* val);

	virtual void Update(float fTime);

	inline void DetachParent() { mpParent = NULL; }
	inline GnNode* GetParent() const { return mpParent; }
	inline GnTimeController* GetControllers() { return mspControls; }
	inline void SetControllers(GnTimeController* val) { mspControls = val; }

protected:
	void RemoveTimeControllerTarget();	
};

GnSmartPointer(GnAVObject);

#endif // GNAVOBJECT_H