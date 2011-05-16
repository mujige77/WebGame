#include "GnSystemPCH.h"
#include "GnSystemEBM.h"
#include "GnMemoryManager.h"

void GnSystemEBM::StartupEBM()
{
	GnMemoryManager::EBMStartup();
}

void GnSystemEBM::ShutdownEBM()
{
	GnMemoryManager::EBMShutdown();
}