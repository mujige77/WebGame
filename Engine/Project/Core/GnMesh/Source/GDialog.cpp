//
//  GDialog.cpp
//  Core
//
//  Created by Max Yoon on 11. 8. 21..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GDialog.h"

GDialog::GDialog(GnInterface* pInterface, GLayer* pLayer) : mpsDialogInterface( pInterface )
	, mpDialogLayer( pLayer ), mpDialogColorLayer( NULL )
{
	
}

GDialog* GDialog::CreateModalColor(GnInterface* pDlgInterface, const guchar ucR, const guchar ucG
	, const guchar ucB, const guchar ucA)
{
	CCLayerColor* colorLayer = CCLayerColor::layerWithColorWidthHeight( ccc4(ucR, ucG, ucB, ucA)
		, GetGameState()->GetGameWidth(), GetGameState()->GetGameHeight() );
	
	GLayer* glayer = new GLayer();
	glayer->addChild( colorLayer, 0 );
	glayer->AddChild( pDlgInterface, 1 );
	
	GDialog* dlg = GnNew GDialog( pDlgInterface, glayer );
	return dlg;
}


gint GDialog::Show()
{
	GScene* curScene = GScene::GetCurrentScene();
	if( curScene == NULL )
		return -1;
	
	gint zorder = curScene->GetMaxZorder() + 1;
	curScene->addChild( mpDialogLayer, zorder );
	mpDialogLayer->release();
	return 1;
}


void GDialog::Close()
{
	GScene* curScene = GScene::GetCurrentScene();
	if( curScene == NULL )
		return;
	
	curScene->removeChild( mpDialogLayer, true );	
}