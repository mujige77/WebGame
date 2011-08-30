//
//  GPositionConvert.h
//  Core
//
//  Created by Max Yoon on 11. 7. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GPositionConvert__
#define __Core__GPositionConvert__

inline static GnVector2 ConvertUIPositionToMeshPosition(GnVector2 cMeshSize, GnVector2 cPosition) 
{
	GnVector2 outPosition;
	cMeshSize.x /= 2;
	cMeshSize.y /= 2;	
	outPosition.x = cPosition.x + cMeshSize.x;
	outPosition.y = GetGameState()->GetGameHeight() - cPosition.y - cMeshSize.y;
	return outPosition;
}

inline static GnFRect GetRectFromCenterPosition(GnVector2 cMeshSize, GnVector2 cPosition)
{
	cPosition.x -= cMeshSize.x / 2;
	cPosition.y -= cMeshSize.y / 2;
	return GnFRect( cPosition.x, cPosition.y, cPosition.x + cMeshSize.x, cPosition.y + cMeshSize.y );
}

inline static void SetUIPosition(GnInterface* pUI, float fPosX, float fPosY)
{
	GnVector2 vec = pUI->GetContentSize();	
	pUI->SetUIPoint( fPosX, fPosY );	
	pUI->SetRect( fPosX, fPosY, fPosX+vec.x, fPosY+vec.y );
}

inline static void SetUIPosition(GnInterface* pUI, float fPosX, float fPosY, gint32 iTegID)
{
	SetUIPosition( pUI, fPosX, fPosY );
	pUI->SetTegID( iTegID );
}
#endif
