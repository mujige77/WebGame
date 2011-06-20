//
//  GCPMove.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GCPMove.h"

GCPMove::GCPMove() : mMoveRange( 1.0f )
{
	
}

void GCPMove::Update(float fDeltaTime)
{
	Gn2DMeshObject* pMesh = GetController()->GetActor()->GetRootNode();
	pMesh->SetPosition( GnVector2(mMoveRange, pMesh->GetPosition().y) );
	
}