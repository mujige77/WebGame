#ifndef GSTAGELEVEL_H
#define GSTAGELEVEL_H

class GStageLevel : public GnMemoryObject
{
public:
	class AttackLine
	{
	public:
		guint32 mNumLine;
		float mStartAppearTime;
		float mIntervalAppearTime;
	};

	class AppearMob
	{
	public:
		guint32 mIndex;
		guint32 mLevel;
		float mIntervalAppearTime;
	};
protected:
	guint32 mLevelIndex;
	guint32 mBossMobIndex;
	GnTPrimitiveArray<AppearMob> mAppearMobs;
	GnTPrimitiveArray<AttackLine> mAttackLines;

public:
	static GStageLevel* CreateStageLevel(const gchar* pcFilePath);

public:
	GStageLevel(){};
	virtual ~GStageLevel(){};
	
	void LoadStream(GnStream* pStream);
	void SaveStream(GnStream* pStream);
	
public:
	inline guint32 GetLevelIndex() {
		return mLevelIndex;
	}
	inline void SetLevelIndex(guint32 val) {
		mLevelIndex = val;
	}
	inline guint32 GetBossMobIndex() {
		return mBossMobIndex;
	}
	inline void SetBossMobIndex(guint32 val) {
		mBossMobIndex = val;
	}
	inline gtuint GetAppearMobCount() {
		return mAppearMobs.GetSize();
	}
	inline GStageLevel::AppearMob& GetAppearMob(gtuint uiIndex) {
		return mAppearMobs.GetAt( uiIndex );
	}
	inline void AddAppearMob(GStageLevel::AppearMob cMob) {
		mAppearMobs.Add( cMob );
	}
	inline gtuint GetAttackLineCount() {
		return mAttackLines.GetSize();
	}
	inline GStageLevel::AttackLine& GetAttackLine(gtuint uiIndex) {
		return mAttackLines.GetAt( uiIndex );
	}
	inline void AddAttackLine(GStageLevel::AttackLine cMob) {
		mAttackLines.Add( cMob );
	}
};

#endif // GSTAGELEVEL_H