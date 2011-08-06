//
//  GCastleForces.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 19..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GCastleForces.h"
#include "GIconGage.h"


GCastleForces* GCastleForces::CreateCastle(GLayer* pInterfaceLayer, GLayer* pCastleLayer
	, GStageInfo* pStageInfo, GStageInfo::GCastleFiles* pFiles
	, GStageInfo::GCastlePositions* pPositions)
{
	GIconGage gage;
	if( CreateCastleGage( pInterfaceLayer, gage ) == false )
		return NULL;
	
	GCastleForces* castle = GnNew GCastleForces();
	if( castle->CreateCastleData( pCastleLayer, pStageInfo, pFiles, pPositions ) == false )
	{
		GnDelete castle;
		return NULL;
	}
	
	castle->SetGageIcon( gage.mpIcon );
	castle->SetCastleGage( gage.mpGage );
	pInterfaceLayer->AddChild( gage.mpIcon, INTERFACE_ZORDER + 1 );
	pInterfaceLayer->AddChild( gage.mpGage, INTERFACE_ZORDER );
	return castle;
}

bool GCastleForces::CreateCastleGage(GLayer* pInterfaceLayer, GIconGage& cOutGage)
{
	cOutGage = CreateIconGage(GnIProgressBar::eHorizontalFromRight
		,"Controll/0_0.png", "Controll/19_6 back.png", "Controll/19_6 progress.png");
	
	if( cOutGage.mpIcon == NULL || cOutGage.mpGage == NULL )
		return false;
	
	float pointX = 0.0f;
	float pointY = 0.0f;
	cOutGage.mpIcon->SetUIPoint( pointX, pointY );	

	pointX = 19.0f;
	pointY = 6.0f;
	cOutGage.mpGage->SetUIPoint( pointX, pointY ); 	
	return true;
}