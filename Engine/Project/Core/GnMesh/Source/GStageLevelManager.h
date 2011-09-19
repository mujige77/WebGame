//
//  GStageLevelManager.h
//  Core
//
//  Created by Max Yoon on 11. 8. 31..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GStageLevelManager_h
#define Core_GStageLevelManager_h

#include "GStageLevel.h"

class GStageLevelManager : public GnMemoryObject
{
public:
	class ReadyAppearMobCtrl
	{
	public:
		guint32 index;
		guint32 level;
		guint32 line;
		
	public:
		ReadyAppearMobCtrl()
		{}
		ReadyAppearMobCtrl(guint32 uiIndex, guint32 uiLevel, guint32 uiLine) : index( uiIndex )
		, level( uiLevel ), line( uiLine )
		{}
	};
	
protected:
	enum
	{
		MAX_APPEARMOB = 200,
	};
	
	class AcumAttackLine
	{
	public:
		guint32 numLine;
		float intervalAppearTime;
		float acumTime;
		
	public:
		AcumAttackLine(guint32 uiNumLine, float fIntervalAppearTime) : numLine( uiNumLine )
			, intervalAppearTime( fIntervalAppearTime ), acumTime( 0.0f )
		{}
	};
	
	class AppearMobCtrl
	{
	public:
		guint32 index;
		guint32 level;
		
	public:
		AppearMobCtrl()
		{}
		AppearMobCtrl(guint32 uiIndex, guint32 uiLevel) : index( uiIndex ), level( uiLevel )
		{}
	};

private:
	GStageLevel* mpStageLevel;
	float mAcumTime;
	float mAcumStartAppearTime;
	GnTPrimitiveSet<AcumAttackLine> mAcumAttackLines;
	AppearMobCtrl mAppearMobs[MAX_APPEARMOB];
	GnTPrimitiveSet<ReadyAppearMobCtrl>  mReadyAppearMobs;
	
public:
	static GStageLevelManager* CreateManager(guint uiNumStage);
	
public:
	virtual ~GStageLevelManager();
	void Update(float fTime);
//	bool IsCreateEnemy();
public:
	inline GStageLevel* GetStageLevel() {
		return mpStageLevel;
	}
	inline gtuint GetAttackLineCount() {
		return mAcumAttackLines.GetSize();
	}
	inline AcumAttackLine& GetAttackLine(gtuint uiIndex) {
		return mAcumAttackLines.GetAt( uiIndex );
	}
	inline void AddAttackLine(AcumAttackLine cLine) {
		mAcumAttackLines.Add( cLine );
	}
	inline gtuint GetReadyAppearMobCount() {
		return mReadyAppearMobs.GetSize();
	}
	inline ReadyAppearMobCtrl& GetReadyAppearMob(gtuint uiIndex) {
		return mReadyAppearMobs.GetAt( uiIndex );
	}
	inline void AddReadyAppearMob(guint32 uiLine, AppearMobCtrl& cMob) {
		mReadyAppearMobs.Add( ReadyAppearMobCtrl( cMob.index, cMob.level, uiLine ) );
	}
	inline void RemoveAllReadyAppearMob() {
		mReadyAppearMobs.RemoveAll();
	}
protected:
	GStageLevelManager(GStageLevel* pStageLevel);
	void Init(GStageLevel* pStageLevel);
	void CollectAppearMobList(GStageLevel* pStageLevel);
	void CheckAddAcumAttackLine();
	AppearMobCtrl& GetAppearFromList();
};

#endif
