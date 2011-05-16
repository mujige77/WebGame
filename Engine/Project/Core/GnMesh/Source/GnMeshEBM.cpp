#include "GnMeshPCH.h"
#include "GnMeshEBM.h"

#include "GnMeshHeader.h"
#include "GnSMTextureAniCtrl.h"
#include "GnSMPostionAniCtrl.h"
#include "GnMeshData.h"
#include "GnMesh.h"
#include "GnScreenMesh.h"
#include "GnSMElement.h"
#include "GnSMGroup.h"


void GnMeshEBM::StartupEBM()
{
	//GnRegisterStream(GnPlaneActor);
	GnRegisterStream(GnSequence);
	GnRegisterStream(GnSMTextureAniCtrl);
	GnRegisterStream(GnMeshData);
	GnRegisterStream(GnMesh);
	GnRegisterStream(GnScreenMesh);
	GnRegisterStream(GnSMElement);
	GnRegisterStream(GnSMGroup);
}

void GnMeshEBM::ShutdownEBM()
{
	//GnUnregisterStream(GnPlaneActor);
	GnUnregisterStream(GnSequence);
	GnUnregisterStream(GnSMTextureAniCtrl);
	GnUnregisterStream(GnMeshData);
	GnUnregisterStream(GnMesh);
	GnUnregisterStream(GnScreenMesh);
	GnUnregisterStream(GnSMElement);
	GnUnregisterStream(GnSMGroup);
}