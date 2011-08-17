//
//  GnITabPage.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 22..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"	
#include "GnITabPage.h"

GnImplementRTTI(GnITabPage, GnInterfaceGroup);
GnITabPage::GnITabPage(const gchar* pcBackgroundName)
{
	if( pcBackgroundName )
		SetBackground( pcBackgroundName );
}
void GnITabPage::SetBackground(const gchar* pcBackgroundName)
{
	Gn2DMeshObject* backgroundMesh = Gn2DMeshObject::CreateFromTextureFile( pcBackgroundName );
	if( backgroundMesh )
	{
		mpsDefaultMesh = backgroundMesh;
		AddMeshToParentNode( backgroundMesh, INTERFACE_ZORDER );
		GnVector2 size = mpsDefaultMesh->GetSize();
		SetContentSize( size.x, size.y );
	}
}