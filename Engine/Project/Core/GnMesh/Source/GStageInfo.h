//
//  GStageInfo.h
//  Core
//
//  Created by Max Yoon on 11. 7. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GStageInfo__
#define __Core__GStageInfo__

class GStageInfo : public GnMemoryObject
{
public:
	class GCastleFiles
	{
	public:
		GCastleFiles();
		~GCastleFiles();
	public:
		GnSimpleString mCastle;
		GnSimpleString mCastleBreak;		
		GnSimpleString mCastleDestroy;
		GnSimpleString mCastleBottom;
		GnSimpleString mCastleDamageEffect;
		GnSimpleString mCastleBreakDamageEffect;
		GnSimpleString mCastleBottomDamageEffect;
		GnSimpleString mDeckEffect;
	};
	
	class GCastlePositions
	{
	public:
		GnVector2 mCastle;
		GnVector2 mCastleBreak;		
		GnVector2 mCastleDestroy;
		GnVector2 mCastleBottom;
		GnVector2 mCastleDamageEffect;
		GnVector2 mCastleBreakDamageEffect;
		GnVector2 mCastleBottomDamageEffect;
		GnVector2 mDeckEffect;		
	};
	
private:
	gtuint mNumStage;
	gtuint mNumLine;
	float mLineHeight;
	bool mUseCastleFile;
	GCastleFiles mEnemyCastleFiles;
	GCastleFiles mForcesCastleFiles;
	GnSimpleString mBackgroundFileName;
	GnSimpleString mInterfaceFileName;
	GnVector2 mInterfaceSize;
	GnVector2 mBackgroundSize;
	
public:
	static bool GetStageInfo(gtuint uiStage, GStageInfo& outStageInfo);
	
public:
	bool GetEnemyCastlePosition(GCastlePositions& cOutPositions);
	bool GetForcesCastlePosition(GCastlePositions& cOutPositions);
	
public:
	inline GCastleFiles* GetEnemyCastleFiles() {
		return &mEnemyCastleFiles;
	}
	inline GCastleFiles* GetForcesCastleFiles() {
		return &mForcesCastleFiles;
	}
	inline const gchar* GetBackgroundFileName() {
		return mBackgroundFileName;
	}
	inline const gchar* GetInterfaceFileName() {
		return mInterfaceFileName;
	}
	inline gtuint GetNumStage() {
		return mNumStage;
	}
	inline GnVector2& GetInterfaceSize() {
		return mInterfaceSize;
	}
	inline GnVector2& GetBackgroundSize() {
		return mBackgroundSize;
	}
	inline gtuint GetNumLine() {
		return mNumLine;
	}
	inline float GetLineHeight() {
		return mLineHeight;
	}
	
protected:
	void Set1_20Stage(gtuint uiStage);
	void Get1_20StagePosition(bool bForces, GCastlePositions& cOutPositions);
};

#endif
