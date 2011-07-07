#ifndef GNANIMATION_H
#define GNANIMATION_H

class Gn2DMeshObject;
GnSmartPointer(GnAnimation);
class GnAnimation : public GnObject
{
	GnDeclareFlags(gushort);
	GnDeclareRTTI;
	GnDeclareAbstractStream;
public:
	enum
	{
		MASK_CREATEDATA = 0x000001,
		MASK_MESHSTREAM = 0x000002,
	};
	class AniInfo : public GnSmartObject
	{
		GnDeclareDataStream;
	protected:
		float mStartTime;
		float mEndTime;

	public:
		inline float GetStartTime() {
			return mStartTime;
		}
		inline void SetStartTime(float val) {
			mStartTime = val;
		}
		inline float GetEndTime() {
			return mEndTime;
		}
		inline void SetEndTime(float val) {
			mEndTime = val;
		}
	};
	typedef GnPointer<AniInfo> AniInfoPtr;
protected:
	GnTObjectArray<AniInfoPtr> mInfos;
	GnObjectForm* mpTarget;
	bool mIsMeshStream;
	float mAniSpeed;
public:
	GnAnimation();
	virtual ~GnAnimation(){};

	virtual bool CreateData() = 0;
	virtual void RemoveData() = 0;
	virtual void SetTarget(GnObjectForm* pObject);
	virtual void Start(float fTime){ GnAssert( false ); }
	virtual void Stop(){ GnAssert( false ); }

	virtual void SetAniInfo(gtuint uiIndex, AniInfo* pInfo) {
		GnAssert( pInfo );
		mInfos.SetAt( uiIndex, pInfo );
	}
	inline gtuint GetAniInfoCount() {
		return mInfos.GetSize();
	}
	inline AniInfo* GetAniInfo(gtuint uiIndex) {
		return mInfos.GetAt( uiIndex );
	}
	inline float GetAniSpeed() {
		return mAniSpeed;
	}
	inline void SetAniSpeed(float val) {
		mAniSpeed = val;
	}
	inline bool IsMeshStream() {
		return GetBit( MASK_MESHSTREAM );
	}
	inline void SetMeshStream(bool val) {
		SetBit( val, MASK_MESHSTREAM );
	}	
	bool IsCreateData() {
		return GetBit( MASK_CREATEDATA );
	}
	void SetCreateData( bool val ) {
		SetBit( val, MASK_CREATEDATA );
	}
	// 툴을 위한 함수들 사용하게 되면 위험함
public:
	inline GnTObjectArray<AniInfoPtr>* GetAniInfos() {
		return &mInfos;
	}
	inline void AddAniInfo(AniInfo* pAniInfo) {
		mInfos.Add( pAniInfo );
	}
};


#endif // GNANIMATION_H