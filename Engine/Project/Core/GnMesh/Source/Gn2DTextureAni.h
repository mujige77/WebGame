#ifndef GNSPRITEANIMATION_H
#define GNSPRITEANIMATION_H

class Gn2DTextureAni : public GnAnimation
{
	GnDeclareRTTI;
	GnDeclareStream;
public:
	class TextureAniInfo : public AniInfo
	{
		GnDeclareDataStream;
	protected:
		gchar* mTextureName;		
		
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
	};
protected:
	CCAnimate* mpAnimate;
	CCSize mSize;
	
public:
	Gn2DTextureAni();
	virtual ~Gn2DTextureAni();

	virtual bool CreateData();
	virtual void RemoveData();
	virtual void Start(float fTime);
	virtual void Stop();

	inline CCAnimate* GetAnimate() {
		return mpAnimate;
	}

protected:
	Gn2DMeshObject* Get2DMeshObject() {
		return (Gn2DMeshObject*)mpTarget;
	}
};

GnSmartPointer(Gn2DTextureAni);
#endif // GNSPRITEANIMATION_H