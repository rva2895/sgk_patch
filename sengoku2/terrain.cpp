#include "stdafx.h"

#include "terrain.h"

#define TERRAIN_COUNT 252

BYTE* terrain_array = 0;
BYTE* terrain_array_UP1 = 0;
BYTE* terrain_array_UP2 = 0;
BYTE* terrain_array_UP3 = 0;
BYTE* terrain_array_UP4 = 0;
/*BYTE terrain_array[] =
{
4, 1, 2, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,	//0
1, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4,	//0x10
4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,	//0x20
4, 4, 4, 1, 4,									//CC terrains end here
4, 4,											//terrains 53, 54
//border terrains
4, 1, 4, 4, 2, 4, 4, 4, 4,	//0x30
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,	//0x40
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,	//0x50
4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0,	//0x60
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0x70
0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0x80
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0x90
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xA0
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xB0
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xC0
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xD0
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xE0
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0xF0
};*/

BYTE indirect_table_water[] =	//starts from 1 (TERR-WATER1)
{
	0, 1, 1, 0,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 0, 0,				//WATER2 and WATER3
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 0		//MARSH
};

#define TERR_MAX_CONST 58 //before MARSH, used for indirect table water

//BYTE indirect_table_water_2[TERR_MAX_CONST+1];

void terrain_transition_change(int state)
{
	//setByte(0x005CBE20, state ? 0xFF : 2);
	indirect_table_water[0] = state;	//WATER1
	indirect_table_water[3] = state;	//WATERSWAMP
	indirect_table_water[21] = state;	//WATER2
	indirect_table_water[22] = state;	//WATER3
	indirect_table_water[58] = state;	//MARSH
										/*for (int i = 0; i < sizeof(indirect_table_water); i++)
										switch (i)
										{
										case 0:
										case 3:
										case 21:
										case 22:
										case 58:
										break;
										default:
										indirect_table_water[i] = !state;
										}*/
}

/*__declspec(naked) void snow_terrain_fix_1() //005CBE92
{
	__asm
	{
		cmp     dl, 20h
		jb      _not_snow1
		cmp     dl, 22h
		jbe     _snow1
		cmp     dl, 47
		jz      _snow1
		cmp     dl, 55
		jz      _snow1
		cmp     dl, 63
		jz      _snow1
		_not_snow1 :
		push    005CBEA1h
			ret
			_snow1 :
		push    005CBEBEh
			ret
	}
}

__declspec(naked) void snow_terrain_fix_2() //005CBEAF
{
	__asm
	{
		cmp     dl, 20h
		jb      _not_snow2
		cmp     dl, 22h
		jbe     _snow2
		cmp     dl, 47
		jz      _snow2
		cmp     dl, 55
		jz      _snow2
		cmp     dl, 63
		jz      _snow2
		_not_snow2 :
		push    005CBEC3h
			ret
			_snow2 :
		push    005CBEBEh
			ret
	}
}

__declspec(naked) void snow_terrain_fix_3() //005CBF42
{
	__asm
	{
		cmp     bl, 20h
		jb      _not_snow3
		cmp     bl, 22h
		jbe     _snow3
		cmp     bl, 47
		jz      _snow3
		cmp     bl, 55
		jz      _snow3
		cmp     bl, 63
		jz      _snow3
		_not_snow3 :
		push    005CBF51h
			ret
			_snow3 :
		push    005CBF89h
			ret
	}
}

__declspec(naked) void snow_terrain_fix_4() //005CBF5D
{
	__asm
	{
		cmp     dl, 20h
		jb      _not_snow4
		cmp     dl, 22h
		jbe     _snow4
		cmp     dl, 47
		jz      _snow4
		cmp     dl, 55
		jz      _snow4
		cmp     dl, 63
		jz      _snow4
		_not_snow4 :
		push    005CBF6Ch
			ret
			_snow4 :
		push    005CBF89h
			ret
	}
}

__declspec(naked) void snow_terrain_fix_5() //005CBF7A
{
	__asm
	{
		cmp     dl, 20h
		jb      _not_snow5
		cmp     dl, 22h
		jbe     _snow5
		cmp     dl, 47
		jz      _snow5
		cmp     dl, 55
		jz      _snow5
		cmp     dl, 63
		jz      _snow5
		_not_snow5 :
		push    005CBF8Eh
			ret
			_snow5 :
		push    005CBF89h
			ret
	}
}

__declspec(naked) void snow_terrain_fix_6() //005CC011
{
	__asm
	{
		cmp     bl, 20h
		jb      _not_snow6
		cmp     bl, 22h
		jbe     _snow6
		cmp     bl, 47
		jz      _snow6
		cmp     bl, 55
		jz      _snow6
		cmp     bl, 63
		jz      _snow6
		_not_snow6 :
		push    005CC020h
			ret
			_snow6 :
		push    005CC055h
			ret
	}
}

__declspec(naked) void snow_terrain_fix_7() //005CC02C
{
	__asm
	{
		cmp     dl, 20h
		jb      _not_snow7
		cmp     dl, 22h
		jbe     _snow7
		cmp     dl, 47
		jz      _snow7
		cmp     dl, 55
		jz      _snow7
		cmp     dl, 63
		jz      _snow7
		_not_snow7 :
		push    005CC03Bh
			ret
			_snow7 :
		push    005CC055h
			ret
	}
}

__declspec(naked) void snow_terrain_fix_8() //005CC049
{
	__asm
	{
		cmp     al, 20h
		jb      _not_snow8
		cmp     al, 22h
		jbe     _snow8
		cmp     al, 47
		jz      _snow8
		cmp     al, 55
		jz      _snow8
		cmp     al, 63
		jz      _snow8
		_not_snow8 :
		push    005CC05Ah
			ret
			_snow8 :
		push    005CC055h
			ret
	}
}

__declspec(naked) void snow_terrain_fix_9() //005CC095
{
	__asm
	{
		cmp     dl, 20h
		jb      _not_snow9
		cmp     dl, 22h
		jbe     _snow9
		cmp     dl, 47
		jz      _snow9
		cmp     dl, 55
		jz      _snow9
		cmp     dl, 63
		jz      _snow9
		_not_snow9 :
		push    005CC1F6h
			ret
			_snow9 :
		push    005CC0ACh
			ret
	}
}

void(__thiscall* rmsDefine) (void* _this, char *str, int flag, int value, char, char, char, char) =
(void(__thiscall*) (void*, char*, int, int, char, char, char, char))0x004E1C20;

void __stdcall mapsize_rms_define(int size, void* _this)
{
	switch (size)
	{
	case 320:
		rmsDefine(_this, "MAPSIZE_320", 1, 0, 0, 0, 0, 0);
		break;
	case 400:
		rmsDefine(_this, "MAPSIZE_400", 1, 0, 0, 0, 0, 0);
		break;
	case 480:
		rmsDefine(_this, "MAPSIZE_480", 1, 0, 0, 0, 0, 0);
		break;
	case 560:
		rmsDefine(_this, "MAPSIZE_560", 1, 0, 0, 0, 0, 0);
		break;
	case 640:
		rmsDefine(_this, "MAPSIZE_640", 1, 0, 0, 0, 0, 0);
		break;
	default:
		break;
	}
}

__declspec(naked) void onMapSizeRMSDefine() //004E7542
{
	__asm
	{
		push    eax
		mov     ecx, esi
		mov     eax, 004E1C20h
		call    eax

		push    esi
		mov     eax, [esi + 14h]
		push    eax
		call    mapsize_rms_define
		push    004E754Ah
		ret
	}
}*/

__declspec(naked) void terrain_asm_1() //004B0CC3
{
	__asm
	{
		add     edx, 4
		cmp     ecx, TERRAIN_COUNT
		mov     eax, 004B0CC9h
		jmp     eax
	}
}

//27 forbidden IDs: 94 to 120

__declspec(naked) void terrain_asm_2() //00583A8F
{
	__asm
	{
		cmp     ebp, 121  //forbidden ID+1
		jg      short not_forbidden
		cmp     ebp, 95
		jge     short loc_583AF7
not_forbidden:
		cmp     [esi - 1Ch], bl
		jz      loc_583AF7
		mov     edx, 007AF609h
		jmp     edx
loc_583AF7:
		mov     edx, 00583AF7h
		jmp     edx
	}
}

__declspec(naked) void terrain_forbidden_ids_2() //0041D574
{
	__asm
	{
		cmp     ecx, 120
		jg      short not_forbidden_2
		cmp     ecx, 94
		jge     short forbidden_2
not_forbidden_2:
		mov     byte ptr [edx + eax + 0D9h], 0
forbidden_2:
		mov     eax, 0041D57Ch
		jmp     eax
	}
}

__declspec(naked) void terrain_asm_3() //0053CA47
{
	__asm
	{
		push    TERRAIN_COUNT
		movsx   edx, word ptr [ebp + 6Eh]
		mov     ecx, 0053CA4Dh
		jmp     ecx
	}
}

__declspec(naked) void terrain_asm_4() //0053C797
{
	__asm
	{
		push    TERRAIN_COUNT
		movsx   edx, word ptr [ebp + 6Eh]
		mov     ecx, 0053C79Dh
		jmp     ecx
	}
}

__declspec(naked) void terrain_asm_5() //0053CE46
{
	__asm
	{
		push    TERRAIN_COUNT
		push    eax
		mov     ecx, [ecx + 0A274h]
		mov     eax, 0053CE4Fh
		jmp     eax
	}
}

__declspec(naked) void terrain_asm_6() //004E5FA6
{
	__asm
	{
		push    TERRAIN_COUNT
		push    eax
		mov     ecx, [ecx + 0BF7Ch]
		mov     edx, 004E5FAFh
		jmp     edx
	}
}

void __cdecl memcpy_new(void* dst, void* src, size_t count)
{
	memcpy(dst, src, count);
}

#define RGE_BORDER_PADDING 0x170 //OK
#define RGE_POST_BORDER_SIZE 0x2D0 //hopefully the same
#define TERRAIN_SIZE 0x1B4 //OK
#define OLD_RGE_SIZE 0xA4E0 //OK
#define OLD_RGE_SIZE_2 0xCD08 //OK
#define NEW_RGE_SIZE (OLD_RGE_SIZE - RGE_BORDER_PADDING + 158 * TERRAIN_SIZE)
#define NEW_RGE_SIZE_2 (NEW_RGE_SIZE+OLD_RGE_SIZE_2-OLD_RGE_SIZE)
#define NEW_RGE_STEP 0xE800

__declspec(naked) void terrain_read_dat_split() //0057F01A
{
	__asm
	{
		xor     ebx, ebx
		push    NEW_RGE_STEP
		push    esi  //buffer
		push    ebp
		mov     dword ptr [esi], 006439F0h
		mov     [esi + 0A274h], ebx
		mov     eax, 00542850h
		call    eax
		push    NEW_RGE_SIZE - NEW_RGE_STEP
		lea     edx, [esi + NEW_RGE_STEP]
		push    edx
		push    ebp
		mov     eax, 00542850h
		call    eax
		//shift RGE
		push    RGE_POST_BORDER_SIZE       //count
		mov     eax, esi
		add     eax, NEW_RGE_SIZE - RGE_POST_BORDER_SIZE  //src
		push    eax
		mov     eax, esi
		add     eax, OLD_RGE_SIZE - RGE_POST_BORDER_SIZE  //dest
		push    eax
		call    memcpy_new
		add     esp, 18h
		mov     eax, 007912A0h
		mov     eax, [eax]
		mov     ecx, 0057F039h
		jmp     ecx
	}
}

void __cdecl terrain_asm_up_1_wrap() //zero out arrays 2, 3, 4
{
	memset(terrain_array_UP2, 0, 256);
	//memset(terrain_array_UP3, 0, 256);
	//memset(terrain_array_UP4, 0, 256);
}

__declspec(naked) void terrain_asm_up_1() //007D6A10
{
	__asm
	{
		call    terrain_asm_up_1_wrap
		dec     ebp
		xor     eax, eax
		cmp     ebp, TERRAIN_COUNT
		jb      short loc_7D6A29
		mov     ebp, TERRAIN_COUNT
loc_7D6A29:
		mov     ebx, 007D6A29h
		jmp     ebx
	}
}

__declspec(naked) void terrain_asm_up_2()//007D6AC8
{
	__asm
	{
		mov     ecx, terrain_array_UP4
		mov     byte ptr [ecx + 0Fh], 0
		mov     ecx, 007D6ACFh
		jmp     ecx
	}
}

int* terrain_language_dll = 0;

void(__thiscall* terrain1_load) (void* this_, int language_dll_id, int terrain) =
	(void(__thiscall*) (void*, int, int))0x005473F0;

void __stdcall terrain_load_1(void* this_)
{
	for (int i = 0; i < TERRAIN_COUNT; i++)
		if (terrain_language_dll[i])
			terrain1_load(this_, terrain_language_dll[i], i);
}

__declspec(naked) void terrain_load_1_wr() //004E171F
{
	__asm
	{
		mov     ecx, [esi + 9F4h]
		push    ecx
		call    terrain_load_1
		mov     ecx, [esi + 9F4h]
		mov     eax, 004E1725h
		jmp     eax
	}
}

void(__thiscall* terrain2_load) (void* this_, int language_dll_id, int terrain) =
	(void(__thiscall*) (void*, int, int))0x00550870;

void __stdcall terrain_load_2(void* this_)
{
	for (int i = 0; i < TERRAIN_COUNT; i++)
		if (terrain_language_dll[i])
			terrain2_load(this_, terrain_language_dll[i], i);
}

__declspec(naked) void terrain_load_2_wr() //004EE349 -> 007BB0DF
{
	__asm
	{
		mov     ecx, [ebp + 0]
		push    ecx
		call    terrain_load_2
		//mov     ecx, [esi + 9F4h]
		//mov     eax, 007BB000h
		mov     ecx, [ebp + 0]
		push    0
		mov     eax, 004EEBAFh
		jmp     eax
	}
}

__declspec(naked) void terrain_up_load_fix() //007D6B0E
{
	__asm
	{
		cmp     ebp, 120
		jg      fix_not_forbidden
		cmp     ebp, 94
		jl      fix_not_forbidden
		mov     eax, 007D6B42h
		jmp     eax
fix_not_forbidden:
		mov     eax, ebp
		lea     ecx, [eax + eax * 2]
		mov     edx, 007D6B13h
		jmp     edx
	}
}

void loadTerrainTxt()
{
	FILE* f;
	fopen_s(&f, "sgk\\terrain.txt", "rt");
	if (f)
	{
		int id;
		int lang;
		int type;
		terrain_language_dll = (int*)malloc(TERRAIN_COUNT * sizeof(int));
		memset(terrain_language_dll, 0, TERRAIN_COUNT * sizeof(int));
		while (fscanf_s(f, "%d,%d,%d", &id, &type, &lang) > 0)
		{
			terrain_array[id] = type;
			terrain_language_dll[id] = lang;
		}
		fclose(f);
	}
	else
	{
		MessageBox(0, "Error: terrain.txt was not found. Check installation integrity.", "Error", MB_ICONERROR);
		exit(0);
	}
}

__declspec(naked) void terrain_memory_fix() //00586411
{
	__asm
	{
		cmp     edx, 40000000h
		jb      no_memory_fix
		mov     edx, 40000000h
no_memory_fix:
		mov     ecx, 190h
		mov     eax, 00586416h
		jmp     eax
	}
}

__declspec(naked) void terrain_sound_fix() //005226BE
{
	__asm
	{
		cmp     eax, 120
		jg      not_forbidden_3
		cmp     eax, 94
		jge     forbidden_3
not_forbidden_3:
		movzx   cx, byte ptr [edx]
		cmp     cx, di
		push    005226C5h
		ret
forbidden_3:
		push    005226D1h
		ret
	}
}

__declspec(naked) void __stdcall terrain_memcpy_fix() //007D865D
{
	__asm
	{
		push edi
	}
		setInt(0x00460BE1, (DWORD)terrain_array_UP4);
		setInt(0x00535581, (DWORD)terrain_array_UP4);
	__asm
	{
		mov     [esp + 10h], esi
		mov     eax, 007D8662h
		jmp     eax
	}
}

void setExtraTerrainHooks()
{
	//editor
	setHook((void*)0x004E171F, terrain_load_1_wr);
	setHook((void*)0x007BB0DF, terrain_load_2_wr);

	setHook((void*)0x007D6B0E, terrain_up_load_fix);

	terrain_array = (BYTE*)malloc(256);
	memset(terrain_array, 0, 256);
	memcpy(terrain_array, (void*)0x0067B468, 42);
	//set new terrain types:
	terrain_array[121] = 4;
	//
	terrain_array_UP1 = (BYTE*)malloc(256);
	memset(terrain_array_UP1, 0, 256);
	memcpy(terrain_array_UP1, (void*)0x007A5740, 48);
	terrain_array_UP2 = (BYTE*)malloc(256);
	terrain_array_UP3 = (BYTE*)malloc(256);
	terrain_array_UP4 = (BYTE*)malloc(256);
	memset(terrain_array_UP2, 0, 256); //?
	memset(terrain_array_UP3, 0, 256);
	memset(terrain_array_UP4, 0, 256);
	//new terrain implementatio:
	//setHook((void*)0x004B0CC3, terrain_asm_1); //sorted out
	setHook((void*)0x007D6A10, terrain_asm_up_1);
	setHook((void*)0x007D6AC8, terrain_asm_up_2);
	setHook((void*)0x00583A8F, terrain_asm_2); //OK
	setHook((void*)0x0053CA47, terrain_asm_3); //OK
	setHook((void*)0x0053C797, terrain_asm_4); //OK
	setHook((void*)0x0053CE46, terrain_asm_5); //OK
	///setHook((void*)0x004E5FA6, terrain_asm_6); //FIX!!!

	//setInt(0x0048FAFD, NEW_RGE_SIZE); //replaced by step above
	//old
	///setInt(0x004946B5, NEW_RGE_SIZE);//""
	///setInt(0x0049473A, NEW_RGE_SIZE);//""
	///setInt(0x0061BFDA, NEW_RGE_SIZE);//""
	///setInt(0x0061CA3A, NEW_RGE_SIZE);//""
	//new
	setInt(0x0040A32A, NEW_RGE_SIZE); //OK
	setInt(0x0040AA9A, NEW_RGE_SIZE); //OK
	//setHook((void*)0x0048FB16, terrain_shift_rge_data);
	setHook((void*)0x0057F01A, terrain_read_dat_split); //OK
	setInt(0x0042660A, NEW_RGE_SIZE_2); //OK
	setInt(0x0042629A, NEW_RGE_SIZE_2); //OK

	setByte(0x0057F087, 0xEB);	//skip border loading, OK
	setByte(0x0057F088, 0x06);

	//UP adds a bunch of references to this array
	setInt(0x005634E5, (DWORD)terrain_array); //OK
	setInt(0x00563D63, (DWORD)terrain_array); //terr const around here, below
	setInt(0x00563D55, TERRAIN_COUNT - 1);
	setInt(0x007B0CC7, (DWORD)terrain_array);
	setInt(0x007D6A2F, (DWORD)terrain_array);
	setInt(0x007D6A46, (DWORD)terrain_array);
	setInt(0x007D6A5F, (DWORD)terrain_array);
	setInt(0x007D6A6E, (DWORD)terrain_array);
	setInt(0x007D6A8F, (DWORD)terrain_array);
	//UP also adds two (or even FOUR?)
	//1st
	setInt(0x007E7611, (DWORD)terrain_array_UP1); //this one needs initialization
	setInt(0x007E7667, (DWORD)terrain_array_UP1);
	//2nd
	setInt(0x00464C8E, (DWORD)terrain_array_UP2);
	setInt(0x00491C8F, (DWORD)terrain_array_UP2);
	//setInt(0x007D6A18, (DWORD)terrain_array_UP2); //replaced with asm
	setInt(0x007D6B3D, (DWORD)terrain_array_UP2);
	//3rd
	setInt(0x007B094A, (DWORD)terrain_array_UP3);
	setInt(0x007B0D3F, (DWORD)terrain_array_UP3);
	setInt(0x007D25BE, (DWORD)terrain_array_UP3);
	setInt(0x007D6A74, (DWORD)terrain_array_UP3);
	setInt(0x007D6A9C, (DWORD)terrain_array_UP3);
	setInt(0x007D6AAE, (DWORD)terrain_array_UP3);
	//4th
	setInt(0x00460BE1, (DWORD)terrain_array_UP4);
	setInt(0x00535581, (DWORD)terrain_array_UP4);
	setInt(0x007D6A4C, (DWORD)terrain_array_UP4);
	setInt(0x007D6A7B, (DWORD)terrain_array_UP4);
	setInt(0x007D6AA4, (DWORD)terrain_array_UP4);
	setInt(0x007D6AB4, (DWORD)terrain_array_UP4);
	
	//setByte(0x004B0CC8, TERRAIN_COUNT); //replace with asm.

	setInt(0x00583A8B, TERRAIN_COUNT); //asm, skip forbidden IDs. OK
	setInt(0x00583A86, 0x467C + TERRAIN_SIZE * (TERRAIN_COUNT - 0x2A)); //OK

	///setByte(0x00495063, TERRAIN_COUNT);
	///setByte(0x00495530, TERRAIN_COUNT);
	setByte(0x00584E1C, TERRAIN_COUNT); //OK

	setByte(0x0057F66E, 0xEB); //skip border unloading

							   //memcpy(indirect_table_water_2, indirect_table_water, TERR_MAX_CONST + 1);

							   //1
	/*setInt(0x005CCA67, (DWORD)indirect_table_water);
	setInt(0x005CCAB6, (DWORD)indirect_table_water);
	setInt(0x005CCAED, (DWORD)indirect_table_water);
	setInt(0x005CCB13, (DWORD)indirect_table_water);
	setInt(0x005CCB3F, (DWORD)indirect_table_water);
	setInt(0x005CCB78, (DWORD)indirect_table_water);
	setInt(0x005CCBAD, (DWORD)indirect_table_water);
	setInt(0x005CCBE7, (DWORD)indirect_table_water);
	setInt(0x005CCC1D, (DWORD)indirect_table_water);
	setInt(0x005CCC80, (DWORD)indirect_table_water);

	//2
	setInt(0x005CBCF8, (DWORD)indirect_table_water);
	setInt(0x005CBD1F, (DWORD)indirect_table_water);
	setInt(0x005CBD45, (DWORD)indirect_table_water);
	setInt(0x005CBD6A, (DWORD)indirect_table_water);
	setInt(0x005CBD91, (DWORD)indirect_table_water);
	setInt(0x005CBDBF, (DWORD)indirect_table_water);
	setInt(0x005CBDE4, (DWORD)indirect_table_water);
	setInt(0x005CBE13, (DWORD)indirect_table_water);
	setInt(0x005CBE4D, (DWORD)indirect_table_water);
	setInt(0x005CBE76, (DWORD)indirect_table_water);

	setInt(0x005CBEE6, (DWORD)indirect_table_water);
	setInt(0x005CBF0B, (DWORD)indirect_table_water);
	setInt(0x005CBF32, (DWORD)indirect_table_water);

	setInt(0x005CBFB5, (DWORD)indirect_table_water);
	setInt(0x005CBFDA, (DWORD)indirect_table_water);
	setInt(0x005CC001, (DWORD)indirect_table_water);

	//3
	setInt(0x005CC0C8, (DWORD)indirect_table_water);
	setInt(0x005CC0EF, (DWORD)indirect_table_water);
	setInt(0x005CC115, (DWORD)indirect_table_water);
	setInt(0x005CC13A, (DWORD)indirect_table_water);
	setInt(0x005CC161, (DWORD)indirect_table_water);
	setInt(0x005CC18B, (DWORD)indirect_table_water);
	setInt(0x005CC1B0, (DWORD)indirect_table_water);
	setInt(0x005CC1D7, (DWORD)indirect_table_water);

	//4
	setInt(0x005CC200, (DWORD)indirect_table_water);
	setInt(0x005CC227, (DWORD)indirect_table_water);
	setInt(0x005CC24E, (DWORD)indirect_table_water);
	setInt(0x005CC274, (DWORD)indirect_table_water);
	setInt(0x005CC299, (DWORD)indirect_table_water);
	setInt(0x005CC2C0, (DWORD)indirect_table_water);
	setInt(0x005CC2EA, (DWORD)indirect_table_water);
	setInt(0x005CC30F, (DWORD)indirect_table_water);
	setInt(0x005CC336, (DWORD)indirect_table_water);

	//1
	setByte(0x005CCA60, TERR_MAX_CONST);
	setByte(0x005CCAAF, TERR_MAX_CONST);
	setByte(0x005CCAE6, TERR_MAX_CONST);
	setByte(0x005CCB0C, TERR_MAX_CONST);
	setByte(0x005CCB38, TERR_MAX_CONST);
	setByte(0x005CCB71, TERR_MAX_CONST);
	setByte(0x005CCBA6, TERR_MAX_CONST);
	setByte(0x005CCBE0, TERR_MAX_CONST);
	setByte(0x005CCC16, TERR_MAX_CONST);
	setByte(0x005CCC75, TERR_MAX_CONST);

	//2
	setByte(0x005CBCF1, TERR_MAX_CONST);
	setByte(0x005CBD18, TERR_MAX_CONST);
	setByte(0x005CBD3E, TERR_MAX_CONST);
	setByte(0x005CBD63, TERR_MAX_CONST);
	setByte(0x005CBD8A, TERR_MAX_CONST);
	setByte(0x005CBDB8, TERR_MAX_CONST);
	setByte(0x005CBDDD, TERR_MAX_CONST);
	setByte(0x005CBE08, TERR_MAX_CONST);
	setByte(0x005CBE46, TERR_MAX_CONST);
	setByte(0x005CBE6F, TERR_MAX_CONST);

	setByte(0x005CBEDF, TERR_MAX_CONST);
	setByte(0x005CBF04, TERR_MAX_CONST);
	setByte(0x005CBF2B, TERR_MAX_CONST);

	setByte(0x005CBFAE, TERR_MAX_CONST);
	setByte(0x005CBFD3, TERR_MAX_CONST);
	setByte(0x005CBFFA, TERR_MAX_CONST);

	//3
	setByte(0x005CC0C1, TERR_MAX_CONST);
	setByte(0x005CC0E8, TERR_MAX_CONST);
	setByte(0x005CC10E, TERR_MAX_CONST);
	setByte(0x005CC133, TERR_MAX_CONST);
	setByte(0x005CC15A, TERR_MAX_CONST);
	setByte(0x005CC184, TERR_MAX_CONST);
	setByte(0x005CC1A9, TERR_MAX_CONST);
	setByte(0x005CC1D0, TERR_MAX_CONST);

	//4
	setByte(0x005CC1F9, TERR_MAX_CONST);
	setByte(0x005CC220, TERR_MAX_CONST);
	setByte(0x005CC247, TERR_MAX_CONST);
	setByte(0x005CC26D, TERR_MAX_CONST);
	setByte(0x005CC292, TERR_MAX_CONST);
	setByte(0x005CC2B9, TERR_MAX_CONST);
	setByte(0x005CC2E3, TERR_MAX_CONST);
	setByte(0x005CC308, TERR_MAX_CONST);
	setByte(0x005CC32F, TERR_MAX_CONST);

	setHook((void*)0x005CBE92, snow_terrain_fix_1);
	setHook((void*)0x005CBEAF, snow_terrain_fix_2);
	setHook((void*)0x005CBF42, snow_terrain_fix_3);
	setHook((void*)0x005CBF5D, snow_terrain_fix_4);
	setHook((void*)0x005CBF7A, snow_terrain_fix_5);
	setHook((void*)0x005CC011, snow_terrain_fix_6);
	setHook((void*)0x005CC02C, snow_terrain_fix_7);
	setHook((void*)0x005CC049, snow_terrain_fix_8);
	setHook((void*)0x005CC095, snow_terrain_fix_9);*/

	//RGE stack array
	/*setInt(0x004DE832, 0x13C + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE96F, 0x13C + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DED39, 0x13C + (TERRAIN_COUNT - 55) * 4);
	//setByte(0x004DE9E0, TERRAIN_COUNT); //replace with asm
	//
	setInt(0x004DE83A, 0x144 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE861, 0x154 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE86E, 0x154 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE889, 0x158 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE8E7, 0x158 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE9B2, 0x154 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE9B9, 0x158 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE854, 0x158 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE8E0, 0x160 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE980, 0x160 + (TERRAIN_COUNT - 55) * 4);
	setInt(0x004DE908, 0x164 + (TERRAIN_COUNT - 55) * 4);*/

	setInt(0x0053CC62, 0x104 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CDB8, 0x104 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CDF4, 0x104 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053D1A4, 0x104 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CC6A, 0x10C + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CC9E, 0x11C + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CE16, 0x11C + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CC91, 0x11C + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CCB9, 0x120 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CD17, 0x120 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CE20, 0x120 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CC7C, 0x120 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CD10, 0x128 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CDC9, 0x128 + (TERRAIN_COUNT - 42) * 4);
	setInt(0x0053CD38, 0x12C + (TERRAIN_COUNT - 42) * 4);

	//0x37 -> 104
	//NEW~
	setInt(0x0053CE03, TERRAIN_COUNT);
	//
	//setByte(0x004DE2E4, TERRAIN_COUNT); //replace with asm.
	//setByte(0x004DE61C, TERRAIN_COUNT); //replace with asm
	//setByte(0x004E5F95, TERRAIN_COUNT); //NOT SURE (0x63), replace with asm?
	//setInt(0x004E5F72, (TERRAIN_COUNT - 0x63) * 4 + 0x190);
	//setInt(0x004E602E, (TERRAIN_COUNT - 0x63) * 4 + 0x190);
	//setByte(0x004E5FA7, TERRAIN_COUNT); //NOT SURE (0x63), replace with asm?

	loadTerrainTxt();

	//TERRAIN CRASH WORKAROUND
	setHook((void*)0x0041D574, terrain_forbidden_ids_2);
	setHook((void*)0x00586411, terrain_memory_fix);
	setHook((void*)0x005226BE, terrain_sound_fix);

	//

	setHook((void*)0x007D865D, terrain_memcpy_fix);
}

//blend array: 0069B600
//reads here: 00610147
//blendomatic unload: 0060A240