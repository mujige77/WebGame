#ifndef GNNODE_H
#define GNNODE_H

class GnTransform;
class GNMAIN_ENTRY GnNode : public GnAVObject
{
	GnDeclareRTTI;
	GnDeclareStream;
protected:
	GnTObjectArray<GnAVObjectPtr> mChildern;

public:
	GnNode(gtuint uiChildSize = 0, GnTransform* pTrans = NULL);
	virtual ~GnNode();

	void AttachChild(GnAVObject* pObject);

	virtual void Update(float fTime);
	virtual GnAVObjectPtr DetachChild(GnAVObject* pChild);
	virtual GnAVObjectPtr DetachChildAt(gtuint uiIndex);
	inline GnAVObject* GetAt(gtuint uiIndex)
	{
		return mChildern.GetAt( uiIndex );
	}
	inline gtuint GetChildCount()
	{
		return mChildern.GetSize();
	}

	virtual GnAVObject* GetObjectByName(const GnSimpleString& strName);
};

GnSmartPointer(GnNode);

#endif // GNNODE_H