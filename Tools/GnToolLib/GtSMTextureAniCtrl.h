#ifndef GTSMTEXTUREANICTRL_H
#define GTSMTEXTUREANICTRL_H
#include "GtTimeController.h"

class GnSMTextureAniCtrl;
GnSmartPointer( GtSMTextureAniCtrl );
class GtSMTextureAniCtrl : public GtTimeController
{
public:
	class AniInfo : public GtStreamObject
	{
	public:
		gint8 mIndex;
		float mStartTime;
		float mEndTime;	
		GnSimpleString mTextureFilePath;
	};
protected:
	GnTPrimitiveArray<AniInfo*> mAniList;

public:
	static GtSMTextureAniCtrl* CreateFromGnData(GnSMTextureAniCtrl* pGnTextureAni);

	GtSMTextureAniCtrl(void);
	~GtSMTextureAniCtrl(void);

	void InsertAniInfo(AniInfo* pInfo);
	void SetAniInfo(gtuint uiIndex, AniInfo* pInfo);
	AniInfo* GetAniInfo(gtuint uiIndex);	
	void RemoveInfo(gtuint uiIndex);
	void RemoveAll();	

	virtual void SaveStream(const gchar* objectName, const gchar* basePath);
	virtual void LoadStream(const gchar* objectName, const gchar* basePath);
	virtual bool ExistSaveData();
	virtual GnTimeController* CreateGnTimeController();

	inline gtuint GetAniInfoCount() {
		return mAniList.GetSize();
	}
	inline GnTPrimitiveArray<AniInfo*>& GetAniList() {
		return mAniList;
	}
}; 

#endif // GTSMTEXTUREANICTRL_H