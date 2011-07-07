#ifndef GN2DTEXTUREANICTLR_H
#define GN2DTEXTUREANICTLR_H

class Gn2DTextureAniCtlr : public GnTimeController
{
	GnDeclareRTTI;
	GnDeclareStream;
public:
	class TextureAniInfo : public GnMemoryObject
	{
		GnDeclareDataStream;
	protected:
		gchar* mTextureName;		
		float mStartTime;
		float mEndTime;
		GnReal2DMesh* mpMesh;

	public:
		TextureAniInfo();
		virtual ~TextureAniInfo();
		inline gchar* GetTextureName() {
			return mTextureName;
		}
		inline void SetTextureName(const gchar* val) {
			if( mTextureName )
				GnFree( mTextureName );
			mTextureName = GnAllocStrcpy( val );
		}
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
		inline void SetMesh(GnReal2DMesh* val) {
			mpMesh = val;
		}
		inline GnReal2DMesh* GetMesh() {
			return mpMesh;
		}
	};
protected:
	GnTPrimitiveArray<TextureAniInfo*> mInfos;
	gtuint mCurrentAniIndex;
	TextureAniInfo* mpCurrentAni;

public:
	Gn2DTextureAniCtlr();
	virtual ~Gn2DTextureAniCtlr();

	virtual bool CreateData();
	virtual void RemoveData();
	virtual void Start(float fTime);
	virtual void Stop();
	virtual void Update(float fDeltaTime);
protected:
	inline Gn2DMeshObject* Get2DMeshObject() {
		return (Gn2DMeshObject*)mpTarget;
	}

	// 툴을 위한 함수들 사용하게 되면 위험함
public:
	inline GnTPrimitiveArray<TextureAniInfo*>* GetAniInfos() {
		return &mInfos;
	}
	inline void AddAniInfo(TextureAniInfo* pAniInfo) {
		mInfos.Add( pAniInfo );
	}
};

#endif // GN2DTEXTUREANICTLR_H