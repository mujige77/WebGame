#ifndef GNSMGROUP_H
#define GNSMGROUP_H

class GNMESH_ENTRY Gn2DNode : public Gn2DMeshObject
{
	GnDeclareRTTI;
	GnDeclareStream;
protected:
	GnTObjectArray<Gn2DMeshObjectPtr> mChildern;

public:
	Gn2DNode(gtuint uiChildSize = 0);
	virtual ~Gn2DNode(){};
	void AttachChild(Gn2DMeshObject* pObject);

	virtual void Update(float fTime);
	//virtual void UpdateRect(bool bUpdateMeshData);
	virtual Gn2DMeshObjectPtr DetachChild(Gn2DMeshObject* pChild);
	virtual Gn2DMeshObjectPtr DetachChildAt(gtuint uiIndex);
	virtual GnObjectForm* GetObjectByName(const GnSimpleString& strName);

	inline Gn2DMeshObject* GetAt(gtuint uiIndex)
	{
		return mChildern.GetAt( uiIndex );
	}
	inline gtuint GetChildCount()
	{
		return mChildern.GetSize();
	}
};

GnSmartPointer(Gn2DNode);
#endif // GNSMGROUP_H
