#ifndef __Core__GnIButton__
#define __Core__GnIButton__

class GnICoolTime;
class GnIButton : public GnInterface
{
public:
	enum eButtonType
	{
		TYPE_NORMAL,
		TYPE_PUSH,
		TYPE_DISABLE,
		TYPE_MAX,
	};
	
public:
	Gn2DMeshObjectPtr mpsNormalMesh;
	Gn2DMeshObjectPtr mpsPushMesh;
	Gn2DMeshObjectPtr mpsDisableMesh;
	GnICoolTime* mpCoolTime;
	GnSimpleString mMeshNames[TYPE_MAX];
	float mCantPushTime;
	
public:
	GnIButton(const gchar* pcDefaultImage, const gchar* pcClickImage = NULL
		, const gchar* pcDisableImage = NULL, eButtonType eDefaultType = TYPE_NORMAL);
	virtual ~GnIButton();
	
	bool CreateNormalImage(const gchar* pcImageName);
	bool CreateClickImage(const gchar* pcImageName);
	bool CreateDisableImage(const gchar* pcImageName);
public:

public:
	virtual bool Push(float fPointX, float fPointY);
	virtual void Pushup(float fPointX, float fPointY);
	virtual void SetIsDisable(bool val);
	virtual void SetIsCantPush(bool val);
	
protected:
	void AddMeshToParentNode(Gn2DMeshObject* pChild);
	void SetPosition(GnVector2& cPos);
	void SetVisibleNormal(bool val);
};

#endif
