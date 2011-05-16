#ifndef GNSMGROUP_H
#define GNSMGROUP_H

class GnSMGroup : public GnSMElement
{
	GnDeclareRTTI;
	GnDeclareStream;
protected:
	GnTObjectArray<GnSMElementPtr> mChildern;

public:
	GnSMGroup(gtuint uiChildSize = 0);
	virtual ~GnSMGroup(){};
	void AttachChild(GnSMElement* pObject);

	virtual void Update(float fTime);
	virtual void UpdateRect(bool bUpdateMeshData);
	virtual GnSMElementPtr DetachChild(GnSMElement* pChild);
	virtual GnSMElementPtr DetachChildAt(gtuint uiIndex);
	virtual GnObjectForm* GetObjectByName(const GnSimpleString& strName);

	inline GnSMElement* GetAt(gtuint uiIndex)
	{
		return mChildern.GetAt( uiIndex );
	}
	inline gtuint GetChildCount()
	{
		return mChildern.GetSize();
	}
};

GnSmartPointer(GnSMGroup);
#endif // GNSMGROUP_H
