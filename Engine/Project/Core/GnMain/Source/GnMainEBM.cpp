#include "GnMainPCH.h"
#include "GnMainEBM.h"

#include "GnTexture.h"
#include "GnTextureProperty.h"


void GnMainEBM::StartupEBM()
{
	GnStreamHelper::EBMStartup();

	GnRegisterStream(GnTextureProperty);
	GnRegisterStream(GnTexture);
}

void GnMainEBM::ShutdownEBM()
{
	GnUnregisterStream(GnTexture);
	GnUnregisterStream(GnTextureProperty);

	GnStreamHelper::EBMShutdown();
}