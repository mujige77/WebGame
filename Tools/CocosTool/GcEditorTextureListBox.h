#pragma once
#include "GcVSListBox.h"

class TextureListInfo
{
public:
	class TextureInfo
	{
	protected:
		CString mTextureName;
		float mStartTime;
		float mEndTime;

	public:
		inline CString GetTextureName() {
			return mTextureName;
		}
		inline void SetTextureName(CString val) {
			mTextureName = val;
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
	};
protected:
	GnTPrimitiveArray<TextureInfo*> mTextures;
	CString mpTextureListInfoName;

public:
	~TextureListInfo()
	{
		for( gtuint i = 0 ; i < mTextures.GetSize() ; i++ )
		{
			delete mTextures.GetAt( i );
		}		
	}
public:
	inline GnTPrimitiveArray<TextureInfo*>* GetTextures() {
		return &mTextures;
	}
	inline CString GetTextureListInfoName() {
		return mpTextureListInfoName;
	}
	inline void SetTextureListInfoName(CString val) {
		mpTextureListInfoName = val;
	}
};

class GcEditorTextureListBox : public GcVSListBox
{
protected:
	bool mEnableAddItem;
	float mDefaultStartTime;
	float mDefaultEndTime;
	TextureListInfo* mpTextureInfo;

public:
	GcEditorTextureListBox() : GcVSListBox(true), mEnableAddItem( true )
		, mDefaultStartTime( 0.0f ), mDefaultEndTime( 1.0f )
	{}
	virtual ~GcEditorTextureListBox(){};

public:
	inline float GetDefaultStartTime() {
		return mDefaultStartTime;
	}
	inline void SetDefaultStartTime(float val) {
		mDefaultStartTime = val;
	}
	inline float GetDefaultEndTime() {
		return mDefaultEndTime;
	}
	inline void SetDefaultEndTime(float val) {
		mDefaultEndTime = val;
	}
	inline TextureListInfo* GetTextureInfo() {
		return mpTextureInfo;
	}
	inline void SetTextureInfo(TextureListInfo* val) {
		mpTextureInfo = val;
	}
	inline GnTPrimitiveArray<TextureListInfo::TextureInfo*>* GetTextureInfos() {
		return mpTextureInfo->GetTextures();
	}

protected:
	void OnBrowse();
	void CreateNewItem();
	BOOL OnBeforeRemoveItem(int iItem);
	void OnAfterAddItem(int iItem);
 	void OnAfterMoveItemUp(int iItem);
 	void OnAfterMoveItemDown(int iItem);
	void OnEndEditLabel(LPCTSTR lpszLabel);

protected:
	void SetTextureInfo(CString strFilePath, float fSartTime, float fEndTime);
	void RenameTexturePath(int iSelItme, CString strFilePath);
};

class GcEditorTextureListListBox : public GcVSListBox
{
protected:
	GnTPrimitiveArray<TextureListInfo*>* mpTextureLists;

public:
	GcEditorTextureListListBox() : GcVSListBox(true), mpTextureLists( NULL ) {
		SetEnableEdit( false );
	}
	virtual ~GcEditorTextureListListBox(){};

public:
	inline GnTPrimitiveArray<TextureListInfo*>* GetTextureLists() {
		return mpTextureLists;
	}
	inline void SetTextureLists(GnTPrimitiveArray<TextureListInfo*>* val) {
		mpTextureLists = val;
	}

protected:
	CString GetMakeName(int count);

protected:
	void CreateNewItem();
	BOOL OnBeforeRemoveItem(int iItem);
	void OnAfterAddItem(int iItem);
};
