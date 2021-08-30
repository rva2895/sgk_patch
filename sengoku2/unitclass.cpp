#include "stdafx.h"
#include "unitclass.h"

__declspec(naked) void onUnitClass6() //0052178C
{
	__asm
	{
		movsx   ecx, word ptr [ecx + 1222h]
		add     eax, ecx
		mov     ecx, 005218B5h
		jmp     ecx
	}
}

void setUnitClassHooks()
{
	setInt(0x00521CFD, 0x90909090);
	setByte(0x00521D01, 0x90);
	setByte(0x00521D02, 0x33);
	setByte(0x00521D03, 0xC0);

	setHook((void*)0x0052178C, onUnitClass6);

	//scout garrison
	setByte(0x00434EE3, 0);
	setByte(0x004C5CA3, 0);
}
