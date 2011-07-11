#pragma once
class Gt2DObject : public GtObject
{
	GnDeclareRTTI;
public:
	const static  gint OBJECT_TYPE = 0;

private:
	Gn2DMeshObjectPtr mpsMesh;
	GnSimpleString mGMFileName;
	guint m2DObjectType;

public:
	Gt2DObject(void);
	~Gt2DObject(void);

public:
	bool SaveData(const gchar* pcBasePath = NULL);	
	bool LoadData();
	bool CreateData();

	gint8 GetType() {
		return OBJECT_TYPE;
	}
	void SetObjectName(const gchar* pcVal);

public:
	inline Gn2DMeshObject* Get2DMeshObjecct() {
		return mpsMesh;
	}
	inline void SetGMFileName(const gchar* pcVal) {
		mGMFileName = pcVal;
	}
	inline const gchar* GetGMFileName() {
		return mGMFileName;
	}
	inline guint Get2DObjectType() {
		return m2DObjectType;
	}
	inline void Set2DObjectType(guint val) {
		m2DObjectType = val;
	}

protected:
	void ChangeTextureAniInfoFileName(const gchar* pcBasePath);
};

GnSmartPointer(Gt2DObject);

