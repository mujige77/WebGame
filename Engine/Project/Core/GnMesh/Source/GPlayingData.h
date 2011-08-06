#ifndef Core_GUserPlayingData_h
#define Core_GUserPlayingData_h

class GPlayingData : public GnMemoryObject
{
	GnDeclareDataStream;
public:
	enum eModeLevel
	{
		eEasy,
		eNormal,
		eHard,
	};
	
public:
	GnSimpleString mPlayerName;
	guint32 mLastClearStage; //
	guint32 mModeLevel; // 0 easy, 1 normal, 2 hard
	guint32 mMoneyCount;
	guint32 mStarCount;
	
public:
	GPlayingData();
	
public:
	inline void SetPlayerName(const gchar* val) {
		mPlayerName = val;
	}
	inline const gchar* GetPlayerName() {
		return mPlayerName;
	}
	inline guint32 GetLastCrearStage() {
		return mLastClearStage;
	}
	inline void SetLastCrearStage(guint32 val) {
		mLastClearStage = val;
	}
	inline guint32 GetModeLevel() {
		return mModeLevel;
	}
	inline void SetModeLevel(guint32 val) {
		mModeLevel = val;
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
	inline void SetStartCount(guint32 val) {
		mStarCount = val;
	}
};

#endif
