#include "GnMainPCH.h"
#include "GnMainEBM.h"

#include "GnTexture.h"
#include "GnTextureProperty.h"
#include "GnExtraData.h"


void GnMainEBM::StartupEBM()
{
	GnStreamHelper::EBMStartup();

	GnRegisterStream(GnTextureProperty);
	GnRegisterStream(GnTexture);
	GnRegisterStream(GnVector2ExtraData);
	GnRegisterStream(GnIntExtraData);
}

void GnMainEBM::ShutdownEBM()
{
	GnUnregisterStream(GnIntExtraData);
	GnUnregisterStream(GnVector2ExtraData);
	GnUnregisterStream(GnTexture);
	GnUnregisterStream(GnTextureProperty);

	GnStreamHelper::EBMShutdown();
}