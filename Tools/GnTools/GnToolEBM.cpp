#include "stdafx.h"
#include "GnToolEBM.h"
#include <GnToolLibEBM.h>

void GnToolEBM::StartupEBM()
{
	// 라이브러리 먼저
	GnToolLibEBM::StartupEBM();
}

void GnToolEBM::ShutdownEBM()
{
	// 라이브러리 마지막
	GnToolLibEBM::ShutdownEBM();
}