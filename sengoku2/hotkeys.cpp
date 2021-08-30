#include "stdafx.h"
#include "hotkeys.h"

struct hotkey
{
	int h;
	int group;
	int id;
};

hotkey hotkeys[] =
{
	//nihonto dojo
	{ 16752,  6,  4 },  //scout ashigaru
	//town center
	{ 16109,  4,  8 },  //yari levy
	//dock
	{ 16187,  5, 10 },  //tekkousen
	{ 16123,  5, 11 },  //murakami kobaya
	//foundry
	{ 16113, 15,  0 },  //teppo sohei
	{ 16049, 15,  1 },  //teppo ashigaru
	{ 16048, 15,  2 },  //boy hiya zutsu
	{ 16081, 15,  3 },  //nanban cannon otomo
	{ 16112, 15,  4 },  //nihon taihou
	{ 16082, 15,  5 },  //dutch culverin otomo
	//nanban trading post
	{ 16080, 16,  0 },  //nanban cannon
	{ 16084, 16,  1 },  //dutch culverin
	//chapel/temple
	{ 16691, 17,  0 },  //jesuit
	{ 16050, 17,  1 },  //bhikku
	//sake den
	{ 16052, 18,  0 },  //horoku dame thrower
	{ 16051, 18,  1 },  //ninja
	{ 16058, 18,  2 },  //hattori shadow
	{ 16053, 18,  3 },  //kanabo senshi
	{ 16054, 18,  4 },  //ronin
	{ 16055, 18,  5 },  //naginata samurai
	{ 16056, 18,  6 },  //nagamaki ronin
	{ 16057, 18,  7 },  //ono bushi
	//villager build
	{ 16179,  3, 30 },  //sake den
};

int currentID;
int currentGroup;

int __fastcall isNewHotkey(int h)
{
	for (int i = 0; i < sizeof(hotkeys) / sizeof(hotkeys[0]); i++)
		if (hotkeys[i].h == h)
		{
			currentGroup = hotkeys[i].group;
			currentID = hotkeys[i].id;
			return 0;
		}
	return h;
}

void* hotkeyTestRet;
void* hotkeyTestCont;

__declspec(naked) void hotkeyTest()
{
	__asm
	{
		push    ecx
		mov     eax, [esp + 8]
		mov     byte ptr [esp + 3], 0
		//cmp     eax, 1             // 9 -> 10
		//ja      _noHK
		//test    eax, eax
		//jz      _noHK

		push    edi
		mov     edi, ecx
		mov     ecx, eax
		call    isNewHotkey
		mov     ecx, edi
		pop     edi
		test    eax, eax
		jnz     _noHK

		lea     edx, [esp + 3]
		push    edx
		lea     edx, [esp + 3]
		push    edx
		lea     edx, [esp + 3]
		push    edx
		mov     eax, currentID
		push    eax
		mov     eax, currentGroup
		push    eax
		mov     eax, hotkeyTestRet
		push    eax
		mov     eax, 0058F3F0h
		jmp     eax
_noHK:
		mov     edx, hotkeyTestCont
		jmp     edx
	}
}

__declspec(naked) void hotkeyTestUnit() //004BD930
{
	__asm
	{
		mov     eax, 004BD991h
		mov     hotkeyTestRet, eax
		mov     eax, 004BD93Ah
		mov     hotkeyTestCont, eax
		jmp     hotkeyTest
	}
}

__declspec(naked) void hotkeyTestBldg() //004BCEA0
{
	__asm
	{
		mov     eax, 004BCEF5h
		mov     hotkeyTestRet, eax
		mov     eax, 004BCEAAh
		mov     hotkeyTestCont, eax
		jmp     hotkeyTest
	}
}

#pragma optimize( "s", on )
void setGroupNumbers() //004BBF30 <- group numbers here
{
	setByte(0x004BBF34, 19); //n groups
	setByte(0x004BE466, 18); //n groups - 1

	setByte(0x004BBF7D, 5);  //group 6
	setByte(0x004BBF72, 12); //group 5
	setByte(0x004BBF67, 9);  //group 4
	//setByte(0x00561478, 7);  //7
	//setByte(0x00561483, 5);  //8  6 -> 5
	//setByte(0x00561499, 5);  //10
	//setByte(0x005614AF, 3);  //12 4 -> 3
	//setByte(0x005614BA, 2);  //13
	//setByte(0x005614F1, 4);  //18
	setByte(0x004BBFA9, 1);  //group 10
	setByte(0x004BBF5C, 31); //group 3

}
#pragma optimize( "", on )

//nihonto dojo, group 6
__declspec(naked) void hotkeyDefaultScoutAshigaru()
{
	__asm
	{
		push    16752
		push    0
		push    0
		push    0
		push    41h  //A
		push    4
		push    6
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

//dock, group 5
__declspec(naked) void hotkeyDefaultTokkousen()
{
	__asm
	{
		push    16187
		push    0
		push    0
		push    0
		push    45h  //E
		push    10
		push    5
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultMurakamiKobaya()
{
	__asm
	{
		push    16123
		push    0
		push    0
		push    0
		push    46h  //F
		push    11
		push    5
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

//foundry, group 15
__declspec(naked) void hotkeyDefaultTeppoSohei()
{
	__asm
	{
		push    16113
		push    0
		push    0
		push    0
		push    53h  //S
		push    0
		push    15
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultTeppoAshigaru()
{
	__asm
	{
		push    16049
		push    0
		push    0
		push    0
		push    41h  //A
		push    1
		push    15
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultBoyHiyaZutsu()
{
	__asm
	{
		push    16048
		push    0
		push    0
		push    0
		push    54h  //T
		push    2
		push    15
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultNanbanCannonOtomo()
{
	__asm
	{
		push    16081
		push    0
		push    0
		push    0
		push    4Eh  //N
		push    3
		push    15
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultNihonTaihou()
{
	__asm
	{
		push    16112
		push    0
		push    0
		push    0
		push    43h  //C
		push    4
		push    15
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultDutchCulverinOtomo()
{
	__asm
	{
		push    16082
		push    0
		push    0
		push    0
		push    44h  //D
		push    5
		push    15
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

//nanban trading post, group 16
__declspec(naked) void hotkeyDefaultNanbanCannon()
{
	__asm
	{
		push    16080
		push    0
		push    0
		push    0
		push    43h  //C
		push    0
		push    16
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultDutchCulverin()
{
	__asm
	{
		push    16084
		push    0
		push    0
		push    0
		push    44h  //D
		push    1
		push    16
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

//chapel/temple, group 17
__declspec(naked) void hotkeyDefaultJesuit()
{
	__asm
	{
		push    16691
		push    0
		push    0
		push    0
		push    4Ah  //J
		push    0
		push    17
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultBhikku()
{
	__asm
	{
		push    16050
		push    0
		push    0
		push    0
		push    42h  //B
		push    1
		push    17
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

//sake den, group 18
__declspec(naked) void hotkeyDefaultHorokuDameThrower()
{
	__asm
	{
		push    16052
		push    0
		push    0
		push    0
		push    53h  //S
		push    0
		push    18
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultNinja()
{
	__asm
	{
		push    16051
		push    0
		push    0
		push    0
		push    5Ah  //Z
		push    1
		push    18
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultHattoriShadow()
{
	__asm
	{
		push    16058
		push    0
		push    0
		push    0
		push    48h  //H
		push    2
		push    18
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaulKanaboSenshi()
{
	__asm
	{
		push    16053
		push    0
		push    0
		push    0
		push    57h  //W
		push    3
		push    18
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultRonin()
{
	__asm
	{
		push    16054
		push    0
		push    0
		push    0
		push    51h  //Q
		push    4
		push    18
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultNaginataSamurai()
{
	__asm
	{
		push    16055
		push    0
		push    0
		push    0
		push    45h  //E
		push    5
		push    18
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultNagamakiRonin()
{
	__asm
	{
		push    16056
		push    0
		push    0
		push    0
		push    52h  //R
		push    6
		push    18
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

__declspec(naked) void hotkeyDefaultOnoBushi()
{
	__asm
	{
		push    16057
		push    0
		push    0
		push    0
		push    41h  //A
		push    7
		push    18
		mov     eax, 0058F490h
		call    eax
		retn    8
	}
}

DWORD hotkeyDefaultsGroup5[] =  //dock
{
	0x004BED33,
	0x004BED4C,
	0x004BED65,
	0x004BED7E,
	0x004BED97,
	0x004BEDB0,
	0x004BF1E3,
	0x004BEDC9,
	0x004BEDE2,
	0x004BEDFB,
	(DWORD)&hotkeyDefaultTokkousen,
	(DWORD)&hotkeyDefaultMurakamiKobaya
};

DWORD hotkeyDefaultsGroup6[] =  //nihonto dojo
{
	0x004BEE28,
	0x004BEE41,
	0x004BEE5A,
	0x004BEE73,
	(DWORD)&hotkeyDefaultScoutAshigaru
};

DWORD hotkeyDefaultsGroup15[] =  //foundry
{
	(DWORD)&hotkeyDefaultTeppoSohei,
	(DWORD)&hotkeyDefaultTeppoAshigaru,
	(DWORD)&hotkeyDefaultBoyHiyaZutsu,
	(DWORD)&hotkeyDefaultNanbanCannonOtomo,
	(DWORD)&hotkeyDefaultNihonTaihou,
	(DWORD)&hotkeyDefaultDutchCulverinOtomo
};

DWORD hotkeyDefaultsGroup16[] =  //nanban trading post
{
	(DWORD)&hotkeyDefaultNanbanCannon,
	(DWORD)&hotkeyDefaultDutchCulverin
};

DWORD hotkeyDefaultsGroup17[] =  //chapel/temple
{
	(DWORD)&hotkeyDefaultJesuit,
	(DWORD)&hotkeyDefaultBhikku
};

DWORD hotkeyDefaultsGroup18[] =  //sake den
{
	(DWORD)&hotkeyDefaultHorokuDameThrower,
	(DWORD)&hotkeyDefaultNinja,
	(DWORD)&hotkeyDefaultHattoriShadow,
	(DWORD)&hotkeyDefaulKanaboSenshi,
	(DWORD)&hotkeyDefaultRonin,
	(DWORD)&hotkeyDefaultNaginataSamurai,
	(DWORD)&hotkeyDefaultNagamakiRonin,
	(DWORD)&hotkeyDefaultOnoBushi
};

__declspec(naked) void hotkeyDispatchGroup15()
{
	__asm
	{
		mov     eax, [esp + 8]
		cmp     eax, 5  //group 15 size - 1
		ja      dispatch_ret_15
		jmp     hotkeyDefaultsGroup15[eax*4]
dispatch_ret_15:
		ret     8
	}
}

__declspec(naked) void hotkeyDispatchGroup16()
{
	__asm
	{
		mov     eax, [esp + 8]
		cmp     eax, 1  //group 16 size - 1
		ja      dispatch_ret_16
		jmp     hotkeyDefaultsGroup16[eax * 4]
dispatch_ret_16:
		ret     8
	}
}

__declspec(naked) void hotkeyDispatchGroup17()
{
	__asm
	{
		mov     eax, [esp + 8]
		cmp     eax, 1  //group 17 size - 1
		ja      dispatch_ret_17
		jmp     hotkeyDefaultsGroup17[eax * 4]
dispatch_ret_17:
		ret     8
	}
}

__declspec(naked) void hotkeyDispatchGroup18()
{
	__asm
	{
		mov     eax, [esp + 8]
		cmp     eax, 7  //group 18 size - 1
		ja      dispatch_ret_18
		jmp     hotkeyDefaultsGroup18[eax * 4]
dispatch_ret_18:
		ret     8
	}
}

DWORD hotkeyGroups[] =
{
	0x004BE875,
	0x004BE474,
	0x004BE9CB,
	0x004BEA37,
	0x004BECBF,
	0x004BED1F,
	0x004BEE14,
	0x004BEE8C,
	0x004BEF04,
	0x004BEF62,
	0x004BEFDA,
	0x004BF01C,
	0x004BF041,
	0x004BF16B,
	0x004BF1C5,
	(DWORD)&hotkeyDispatchGroup15,
	(DWORD)&hotkeyDispatchGroup16,
	(DWORD)&hotkeyDispatchGroup17,
	(DWORD)&hotkeyDispatchGroup18
};

__declspec(naked) void hotkeyOptionsLoad() //004BCE91
{
	__asm
	{
		push    edi
		mov     edi, 0058F670h

		//nihonto dojo
		push    19077        //scout ashigaru
		push    4            //id
		push    6            //group
		mov     ecx, esi
		call    edi

		//dock
		push    19281        //tekkousen
		push    10           //id
		push    5            //group
		mov     ecx, esi
		call    edi

		push    19032        //murakami kobaya
		push    11           //id
		push    5            //group
		mov     ecx, esi
		call    edi

		//town center
		push    19287        //yari levy
		push    8            //id
		push    4            //group
		mov     ecx, esi
		call    edi

		//foundry
		push    19081        //teppo sohei
		push    0            //id
		push    15           //group
		mov     ecx, esi
		call    edi

		push    19078        //teppo ashigaru
		push    1            //id
		push    15           //group
		mov     ecx, esi
		call    edi

		push    19079        //boy hiya zutsu
		push    2            //id
		push    15           //group
		mov     ecx, esi
		call    edi

		push    19033        //nanban cannon otomo
		push    3            //id
		push    15           //group
		mov     ecx, esi
		call    edi

		push    19080        //nihon taihou
		push    4            //id
		push    15           //group
		mov     ecx, esi
		call    edi

		push    19266        //dutch culverin otomo
		push    5            //id
		push    15           //group
		mov     ecx, esi
		call    edi

		//nanban trading post
		push    19265        //nanban cannon
		push    0            //id
		push    16           //group
		mov     ecx, esi
		call    edi

		push    19263        //dutch culverin
		push    1            //id
		push    16           //group
		mov     ecx, esi
		call    edi

		//chapel/temple
		push    19071        //jesuit
		push    0            //id
		push    17           //group
		mov     ecx, esi
		call    edi

		push    19022        //bhikku
		push    1            //id
		push    17           //group
		mov     ecx, esi
		call    edi

		//sake den
		push    19046        //horoku dame thrower
		push    0            //id
		push    18           //group
		mov     ecx, esi
		call    edi

		push    19082        //ninja
		push    1            //id
		push    18           //group
		mov     ecx, esi
		call    edi

		push    19329        //hattori shadow
		push    2            //id
		push    18           //group
		mov     ecx, esi
		call    edi

		push    19037        //kanabo senshi
		push    3            //id
		push    18           //group
		mov     ecx, esi
		call    edi

		push    19036        //ronin
		push    4            //id
		push    18           //group
		mov     ecx, esi
		call    edi

		push    19039        //naginata samurai
		push    5            //id
		push    18           //group
		mov     ecx, esi
		call    edi

		push    19057        //nagamaki ronin
		push    6            //id
		push    18           //group
		mov     ecx, esi
		call    edi

		push    19042        //ono bushi
		push    7            //id
		push    18           //group
		mov     ecx, esi
		call    edi

		//villager build
		push    20019        //sake den
		push    30           //id
		push    3            //group
		mov     ecx, esi
		call    edi

		pop     edi
		pop     esi
		ret     4
	}
}

__declspec(naked) void hotkeyDefaultSet() //007E4CBF
{
	__asm
	{
		push    edi
		mov     edi, 004BE460h

		//nihonto dojo
		push    4            //scout ashigaru
		push    6
		mov     ecx, esi
		call    edi

		//dock
		push    10           //tekkousen
		push    5
		mov     ecx, esi
		call    edi

		push    11           //murakami kobaya
		push    5
		mov     ecx, esi
		call    edi

		//town center
		push    8            //yari levy
		push    4
		mov     ecx, esi
		call    edi

		//foundry
		push    0            //teppo sohei
		push    15
		mov     ecx, esi
		call    edi

		push    1            //teppo ashigaru
		push    15
		mov     ecx, esi
		call    edi

		push    2            //boy hiya zutsu
		push    15
		mov     ecx, esi
		call    edi

		push    3            //nanban cannon otomo
		push    15
		mov     ecx, esi
		call    edi

		push    4            //nihon taihou
		push    15
		mov     ecx, esi
		call    edi

		push    5            //dutch culverin otomo
		push    15
		mov     ecx, esi
		call    edi

		//nanban trading post
		push    0            //nanban cannon
		push    16
		mov     ecx, esi
		call    edi

		push    1            //dutch culverin
		push    16
		mov     ecx, esi
		call    edi

		//chapel/temple
		push    0            //jesuit
		push    17
		mov     ecx, esi
		call    edi

		push    1            //bhikku
		push    17
		mov     ecx, esi
		call    edi

		//sake den
		push    0            //horoku dame thrower
		push    18
		mov     ecx, esi
		call    edi

		push    1            //ninja
		push    18
		mov     ecx, esi
		call    edi

		push    2            //hattori shadow
		push    18
		mov     ecx, esi
		call    edi

		push    3            //kanabo senshi
		push    18
		mov     ecx, esi
		call    edi

		push    4            //ronin
		push    18
		mov     ecx, esi
		call    edi

		push    5            //naginata samurai
		push    18
		mov     ecx, esi
		call    edi

		push    6            //nagamaki ronin
		push    18
		mov     ecx, esi
		call    edi

		push    7            //ono bushi
		push    18
		mov     ecx, esi
		call    edi

		//villager build
		push    30           //sake den
		push    3
		mov     ecx, esi
		call    edi

		pop     edi
		pop     esi
		ret
	}
}

__declspec(naked) void addGroupNumbersForNewGroups1() //004BBFD4
{
	__asm
	{
		push    edi
		push    1
		push    0Eh
		mov     ecx, esi
		mov     edi, 0058F7A0h
		call    edi

		push    6
		push    15
		mov     ecx, esi
		call    edi

		push    2
		push    16
		mov     ecx, esi
		call    edi

		push    2
		push    17
		mov     ecx, esi
		call    edi

		push    8
		push    18
		mov     ecx, esi
		call    edi

		pop     edi
		mov     eax, 004BBFDFh
		jmp     eax
	}
}

__declspec(naked) void addGroupNumbersForNewGroups2() //004BC0A3
{
	__asm
	{
		push    edi
		push    4E31h
		push    0Eh
		mov     ecx, esi
		mov     edi, 0058F6B0h
		call    edi

		push    20006
		push    15
		mov     ecx, esi
		call    edi

		push    20018
		push    16
		mov     ecx, esi
		call    edi

		push    20016
		push    17
		mov     ecx, esi
		call    edi

		push    20019
		push    18
		mov     ecx, esi
		call    edi

		pop     edi
		mov     eax, 004BC0B1h
		jmp     eax
	}
}

__declspec(naked) void group4() //004BECCE
{
	__asm
	{
		jz      loc_4BECD4
		cmp     eax, 1
		jnz     loc_ret
		push    16109
		push    0
		push    0
		push    0
		push    57h
		push    8
		push    4
		mov     eax, 0058F490h
		call    eax
loc_ret:
		ret     8
loc_4BECD4:
		mov     eax, 004BECD4h
		jmp     eax
	}
}

__declspec(naked) void group3() //007E4CD0
{
	__asm
	{
		cmp     eax, 1Dh
		ja      short loc_check_group3
		mov     edx, 007E4CD5h
		jmp     edx
loc_check_group3:
		cmp     eax, 1Eh
		ja      short locret_7E4CDC
		push    16179
		push    0
		push    0
		push    0
		push    52h  //R
		push    30
		push    3
		mov     eax, 0058F490h
		call    eax
locret_7E4CDC:
		retn    8
	}
}

void setHotkeysHooks()
{
	setGroupNumbers();

	setHook((void*)0x004BCE91, hotkeyOptionsLoad);
	setHook((void*)0x004BD930, hotkeyTestUnit);
	setHook((void*)0x004BCEA0, hotkeyTestBldg);

	setHook((void*)0x007E4CBF, hotkeyDefaultSet);

	setHook((void*)0x004BBFD4, addGroupNumbersForNewGroups1);
	setHook((void*)0x004BC0A3, addGroupNumbersForNewGroups2);
	
	setHook((void*)0x004BECCE, group4);
	setHook((void*)0x007E4CD0, group3);

	setByte(0x004BED25, 11);
	setInt(0x004BED2F, (DWORD)hotkeyDefaultsGroup5);

	setByte(0x004BEE1A, 4);
	setInt(0x004BEE24, (DWORD)hotkeyDefaultsGroup6);

	setInt(0x004BE470, (DWORD)hotkeyGroups);

	setHook((void*)0x004BEFE3, (void*)0x004BF1E3); //remove id 1 from shrine
	setHook((void*)0x004BC5AC, (void*)0x004BC5B7);
	setHook((void*)0x004BCD81, (void*)0x004BCD91);
}
