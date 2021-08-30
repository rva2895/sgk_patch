// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "cliff.h"
#include "5thres.h"
#include "terrain.h"
#include "palette.h"
#include "unitclass.h"
#include "hotkeys.h"

void setHooks()
{
	if (!LoadLibrary("sgk\\sengoku.dll"))
	{
		MessageBox(0, "Error Failed to load required library ""sengoku.dll"".\n"
			"Make sure Sengoku: War of The Daimyo was installed correctly", "Error", MB_ICONERROR);
		exit(0);
	}
	set5thResHooks();
	setExtraTerrainHooks();
	setPaletteHooks();

	setByte(0x004CA4DB, 0x90); //scenario building rotation
	setByte(0x004CA4DC, 0x90);

	setByte(0x00585D2F, 0xEB); //terrain paint crash

	setUnitClassHooks();

	setHotkeysHooks();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		setHooks();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

