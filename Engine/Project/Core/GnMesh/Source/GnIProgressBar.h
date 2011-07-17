//
//  GnIProgressBar.h
//  Core
//
//  Created by Max Yoon on 11. 7. 15..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GnIProgressBar__
#define __Core__GnIProgressBar__

#include "GnInterface.h"
class GnIProgressBar : public GnInterface
{
public:
	enum ePlayPlag
	{
		PLAY,
		STOP,
	};
	enum eProgressType
	{
		/// Horizontal Left-Right
		eHorizontalFromLeft,
		/// Horizontal Right-Left
		eHorizontalFromRight,
		/// Vertical Bottom-top
		eVerticalFromBottom,
		/// Vertical Top-Bottom
		eVerticalFromTop,
	};
private:
	Gn2DMeshObjectPtr mpsProgressMesh;
	ePlayPlag mPlayPlag;
	eProgressType mProgressType;
	float mProgressTime;
	float mAcumtime;
	float mProgressWidth;
	float mProgressHeight;
	GnVector2 mOriginalPosition;
	
public:
	static GnIProgressBar* Create(eProgressType eType, const gchar* pcBackImageName = NULL
		, const gchar* pcProgressImagaeName = NULL);
	static GnIProgressBar* Create(eProgressType eType, float fWidth, float fHeight);
	
// func	
public:
	void SetProgressPercent(gtuint uiPercent);
	void ProgressFromLeft(float fSize);
	void ProgressFromRight(float fSize);
	void ProgressFromTop(float fSize);
	void ProgressFromBottom(float fSize);
// virtual	
public:
	void Update(float fDeltaTime);	
	void SetPosition(GnVector2& cPos);
	
protected:
	GnIProgressBar(eProgressType eType, Gn2DMeshObject* pBackMesh, Gn2DMeshObject* pCoolTimeMesh);
	
public:
	inline ePlayPlag GetPlayPlag() {
		return mPlayPlag;
	}
	inline void SetVisibleBackground(bool bVal) {
		mpsDefaultMesh->SetVisible( bVal );
	}
	inline void SetBlindColor(GnColor cColor) {
		mpsDefaultMesh->SetColor( cColor );
	}
	inline void SetBlindAlpha(float val) {
		mpsDefaultMesh->SetAlpha( val );
	}
	inline void SetVisibleProgress(bool bVal) {
		mpsProgressMesh->SetVisible( bVal );
	}
	inline void SetProgressTime(float fTime) {
		mProgressTime = fTime;
	}
	inline void SetProgressColor(GnColor cColor) {
		mpsProgressMesh->SetColor( cColor );
	}
	inline void SetCoolTimeAlpha(float val) {
		mpsProgressMesh->SetAlpha( val );
	}
	inline void Start() {
		mAcumtime = mProgressTime;
		SetVisibleProgress( true );
		//mpsProgressMesh->SetPosition( mOriginalPosition );
		mpsProgressMesh->GetMesh()->setContentSize( CCSizeMake( mProgressWidth, mProgressHeight ) );
		mPlayPlag = PLAY;
	}
	inline void Stop() {
		SetVisibleProgress( false );
		mPlayPlag = STOP;
	}
};

#endif
