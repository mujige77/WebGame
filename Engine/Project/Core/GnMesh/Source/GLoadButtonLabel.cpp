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
		"StartScene/Load/294_130 E.png",
		"StartScene/Load/284_130 N.png",
		"StartScene/Load/294_130 H.png"
	};
	
	label->CreateDefaultImage( modeName[uiModeLevel] );
	label->CreateLabelStage( uiNumStage );
	label->SetPosition( uiNumButton, uiModeLevel );
	label->GetParentUseNode()->addChild( label->mLabelNumStage.GetParentUseNode(), INTERFACE_ZORDER + 1 );
	return label;
}

void GLoadButtonLabel::CreateLabelStage(guint32 uiNumStage)
{
	gstring fullPath;
	GetFullPathFromWorkPath( "StartScene/Load/386_129.png", fullPath );
	
	mLabelNumStage.Init( "0", fullPath.c_str(), 12, 18, '.' );
	mLabelNumStage.SetMaxDigit( 2, "%02d" );
	mLabelNumStage.SetNumber( uiNumStage );
}

void GLoadButtonLabel::SetPosition(gtuint uiNumButton, guint32 uiModeLevel)
{
	float modePositionX = 0.0f;
	float modePositionY = 0.0f;
	float numStagePositionX = .0f;
	float numStagePositionY = .0f;
	
	if( uiNumButton == 0 )
	{
		modePositionY = 130.0f;
		numStagePositionY = 130.0f;
	}
	else if( uiNumButton == 1 )
	{
		modePositionY = 169.0f;
		numStagePositionY = 169.0f;		
	}
	else
	{
		modePositionY = 207.0f;
		numStagePositionY = 207.0f;
	}
	
	if( uiModeLevel == 1 )
		modePositionX = 284.0f;
	else
		modePositionX = 294.0f;

	numStagePositionX = 391.0f;
	
	SetUIPosition( this, modePositionX, modePositionY );
	SetUIPosition( &mLabelNumStage, numStagePositionX, numStagePositionY );
}