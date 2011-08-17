//
//  GLoadButtonLabel.cpp
//  Core
//
//  Created by Max Yoon on 11. 8. 5..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GLoadButtonLabel.h"

GLoadButtonLabel* GLoadButtonLabel::CreateLabel(gtuint uiNumButton, guint32 uiModeLevel, guint32 uiNumStage)
{
	GLoadButtonLabel* label = GnNew GLoadButtonLabel();
	const gchar* modeName[3] = {
		"StartScene/level select/340_131 340_169 340_206.png",
		"StartScene/level select/340_131 340_169 340_206.png",
		"StartScene/level select/340_131 340_169 340_206.png"
	};
	
	label->CreateDefaultImage( modeName[uiModeLevel] );
	label->CreateLabelStage( uiNumStage );
	label->SetPosition( uiNumButton, uiModeLevel );
	label->GetParentUseNode()->addChild( label->mLabelNumStage.GetParentUseNode(), INTERFACE_ZORDER + 1 );
	//label->SetIsDisableCantpushBlind( true );
	label->SetIsCantPush( true );
	return label;
}

void GLoadButtonLabel::CreateLabelStage(guint32 uiNumStage)
{
	gstring fullPath;
	GetFullPathFromWorkPath( "StartScene/level select/386_129.png", fullPath );
	
	mLabelNumStage.Init( "0", fullPath.c_str(), 12, 18, '.' );
	mLabelNumStage.SetMaxDigit( 2, "%02d" );
	mLabelNumStage.SetNumber( uiNumStage );
}

void GLoadButtonLabel::SetPosition(gtuint uiNumButton, guint32 uiModeLevel)
{
	float modePositionX = 0.0f;
	float stagePositionY = 0.0f;
	float numStagePositionX = .0f;
	float numStagePositionY = .0f;
	
	if( uiNumButton == 0 )
	{
		stagePositionY = 130.0f;
		numStagePositionY = 127.0f;
	}
	else if( uiNumButton == 1 )
	{
		stagePositionY = 170.0f;
		numStagePositionY = 167.0f;		
	}
	else
	{
		stagePositionY = 210.0f;
		numStagePositionY = 207.0f;
	}
	
	if( uiModeLevel == 1 )
		modePositionX = 340.0f;
	else
		modePositionX = 340.0f;

	numStagePositionX = 391.0f;
	
	SetUIPosition( this, modePositionX, stagePositionY );
	SetUIPosition( &mLabelNumStage, numStagePositionX, numStagePositionY );
}