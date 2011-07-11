#include "GnMainPCH.h"
#include "GnAVObject.h"
#include "GnTransform.h"
#include "GnNode.h"
GnImplementRTTI(GnAVObject, GnObjectForm);

GnAVObject::GnAVObject(GnTransform* pTrans) : mpParent(NULL), mpTransform(pTrans)
{
}

GnAVObject::~GnAVObject()
{
	RemoveTimeControllerTarget();
	if( mpTransform )
		GnDelete mpTransform;
}

void GnAVObject::AttachParent(GnNode* val)
{
	if( mpParent )
		mpParent->DetachChild(this);

	mpParent = val;
}

void GnAVObject::Update(float fTime)
{
	GnTimeController* pkControl = GetTimeControllers();
	while( pkControl )
	{
		pkControl->Update(fTime);
		pkControl = pkControl->GetNext();
	}
}

void GnAVObject::RemoveTimeControllerTarget()
{
	GnTimeController* pkControl = GetTimeControllers();
	while( pkControl )
	{
		pkControl->SetTargetObject((GnAVObject*)NULL);
		pkControl = pkControl->GetNext();
	}
}