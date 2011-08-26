#ifndef Core_GUserPlayingData_h
#define Core_GUserPlayingData_h

#include "GGameDefine.h"

class GPlayingData : public GnSmartObject
{
	GnDeclareDataStream;
public:
	struct ModeInfo
	{
		bool mEnableMode;
		guint32 mModeLevel; // 0 easy, 1 normal, 2 hard		
		guint32 mLastClearStage;
	};
	
public:
	GnSimpleString mPlayerName;
	GnTPrimitiveArray<ModeInfo> mModeInfos;
	guint32 mMoneyCount;
	guint32 mStarCount;
	eModeLevel mCurrentMode;
	
public:
	GPlayingData();
	
public:
	inline void SetPlayerName(const gchar* val) {
		mPlayerName = val;
	}
	inline const gchar* GetPlayerName() {
		return mPlayerName;
	}
	inline ModeInfo& GetModeInfo(eModeLevel eLevel) {
		return mModeInfos.GetAt( eLevel );
	}
	inline void SetModeInfo(eModeLevel eLevel, ModeInfo cInfo) {
		mModeInfos.SetAt( eLevel, cInfo );
	}
	inline guint32 GetMoneyCount() {
		return mMoneyCount;
	}
	inline void SetMoneyCount(guint32 val) {
		mMoneyCount = val;
	}
	inline guint32 GetStarCount() {
		return mStarCount;
	}
	inline void SetStarCount(guint32 val) {
		mStarCount = val;
	}
	inline void SetCurrentMode(eModeLevel val) {
		GnAssert( val != eMaxMode );
		mCurrentMode = val;
	}
	inline eModeLevel GetCurrentMode() {
		return mCurrentMode;
	}
	inline ModeInfo& GetCurrentModeInfo() {
		return mModeInfos.GetAt( mCurrentMode );
	}
};

GnSmartPointer(GPlayingData);
#endif
