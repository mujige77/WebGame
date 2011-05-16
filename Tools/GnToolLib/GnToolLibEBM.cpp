#include "GnToolLibPCH.h"
#include "GnToolLibEBM.h"
#include "GnToolManager.h"
#include "GtToolSettings.h"
#include "GtObjectManager.h"
#include <GnSystemEBM.h>
#include <GnMainEBM.h>
#include <GnMeshEBM.h>


void GnToolLibEBM::StartupEBM()
{
	// 라이브러리 문저
	GnSystemEBM::StartupEBM();
	GnMainEBM::StartupEBM();
	GnMeshEBM::StartupEBM();
	GnToolManager::StartupEBM();
	
	GtToolSettings::EBMStartup();
	GtObjectManager::EBMStartup();
}

void GnToolLibEBM::ShutdownEBM()
{
	GtObjectManager::EBMShutdown();
	GtToolSettings::EBMShutdown();

	GnToolManager::ShutdownEBM();
	GnMeshEBM::ShutdownEBM();
	GnMainEBM::ShutdownEBM();	
	GnSystemEBM::ShutdownEBM();	
}