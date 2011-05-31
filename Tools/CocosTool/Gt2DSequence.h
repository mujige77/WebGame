#pragma once

class Gt2DSequence : public GtObject
{
	GnDeclareRTTI;
protected:	
	GtConvertString mFileName;
	Gn2DSequence* mpSequence;

public:
	Gt2DSequence(void);
	virtual ~Gt2DSequence(void);	
	void ChangeTextureFile(gtuint uiAniIndex, gtuint aniInfoIndex, const char* pcFileName);
	void ChangeTime(gtuint uiAniIndex, float fTime);

	virtual bool SaveData(const gchar* folderName, const gchar* pcBasePath);
	virtual void SetObjectName(const gchar* pcVal);

	inline Gn2DSequence* GetSequence() {
		return mpSequence;
	}
	inline void SetSequence(Gn2DSequence* val) {
		mpSequence = val;
	}
	inline GnTObjectArray<Gn2DTextureAniPtr>& GetTextureAnis() {
		return mpSequence->GetTextureAnis();
	}
	inline gtuint GetTextureAniCount() {
		return mpSequence->GetTextureAnis().GetSize();
	}
	inline void AddTextureAni(Gn2DTextureAni* pAni) {
		SetModifed( true );
		mpSequence->GetTextureAnis().Add( pAni );
	}
	inline void SetTextureAni(gtuint uiIndex, Gn2DTextureAni* pAni) {
		SetModifed( true );
		mpSequence->GetTextureAnis().SetAt( uiIndex, pAni );
	}
	inline Gn2DTextureAni* GetTextureAni(gtuint uiIndex) {
		return mpSequence->GetTextureAnis().GetAt( uiIndex );
	}
	inline void RemoveAtAndFillAllAni(gtuint uiIndex) {
		SetModifed( true );
		mpSequence->GetTextureAnis().RemoveAtAndFillAll( uiIndex );
	}
	inline GtConvertString GetFileName() {
		return mFileName;
	}
	inline void SetFileName(GtConvertString val) {
		mFileName = val;
	}
};

GnSmartPointer(Gt2DSequence);
