#include "GnMeshPCH.h"
#include "GnMeshEBM.h"

#include "GnMeshHeader.h"
#include "GnSMTextureAniCtrl.h"
#include "GnSMPostionAniCtrl.h"
#include "GnMeshData.h"
#include "GnMesh.h"
#include "GnScreenMesh.h"
#include "Gn2DMeshObject.h"
#include "Gn2DNode.h"


void GnMeshEBM::StartupEBM()
{
	//GnRegisterStream(Gn2DActor);
	GnRegisterStream(GnSequence);
	GnRegisterStream(Gn2DSequence);
	GnRegisterStream(GnSMTextureAniCtrl);
	GnRegisterStream(GnMeshData);
	GnRegisterStream(GnMesh);
	GnRegisterStream(GnScreenMesh);
	GnRegisterStream(Gn2DMeshObject);
	GnRegisterStream(Gn2DNode);
	GnRegisterStream(Gn2DAVData);
	GnRegisterStream(Gn2DTextureAni);

	GnSceneManager::_StartupEBM();	
}

void GnMeshEBM::ShutdownEBM()
{
	GnSceneManager::_ShutdownEBM();

	//GnUnregisterStream(Gn2DActor);
	GnUnregisterStream(GnSequence);
	GnUnregisterStream(Gn2DSequence);
	GnUnregisterStream(GnSMTextureAniCtrl);
	GnUnregisterStream(GnMeshData);
	GnUnregisterStream(GnMesh);
	GnUnregisterStream(GnScreenMesh);
	GnUnregisterStream(Gn2DMeshObject);
	GnUnregisterStream(Gn2DNode);
	GnUnregisterStream(Gn2DAVData);
	GnUnregisterStream(Gn2DTextureAni);
}