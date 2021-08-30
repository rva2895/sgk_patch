#include "stdafx.h"

void* resedit_text = 0;
void* resedit_edit = 0;

__declspec(naked) void create_text() //004E9024
{
	__asm
	{
		mov     ecx, [esi + 918h]
		mov     eax, offset resedit_text
		push    42206
		push    eax
		push    ecx
		mov     ecx, esi
		mov     eax, 004EDDD0h
		call    eax
		test    eax, eax
		jz      loc_4EB3A6
		lea     eax, [esi + 0A3Ch]
		mov     edx, 004E9030h
		jmp     edx
loc_4EB3A6:
		mov     ecx, 004EB3A6h
		jmp     ecx
	}
}

__declspec(naked) void create_edit() //004E9103
{
	__asm
	{
		mov     edi, offset resedit_edit
		mov     ecx, [esi + 918h]
		push    0
		push    0
		push    3
		push    5
		push    006784E4h //"0"
		push    edi
		push    ecx
		mov     ecx, esi
		mov     eax, 004EDE70h
		call    eax
		test    eax, eax
		jz      loc_4EB3A6
		mov     ecx, [esi + 0A58h]
		mov     eax, 004E9109h
		jmp     eax
loc_4EB3A6:
		mov     ecx, 004EB3A6h
		jmp     ecx
	}
}

__declspec(naked) void edit_delete() //004EEFD9
{
	__asm
	{
		mov     edi, 005E7310h
		mov     eax, offset resedit_text
		push    eax
		call    edi
		mov     eax, offset resedit_edit
		push    eax
		call    edi
		lea     ecx, [esi + 0AD4h]
		mov     eax, 004EEFDFh
		jmp     eax
	}
}

__declspec(naked) void setrect() //004EC161
{
	__asm
	{
		push    14h
		push    46h
		push    46
		push    350
		mov     ecx, resedit_text
		mov     edx, [ecx]
		call    dword ptr [edx + 1Ch]
		push    14h
		push    46h
		push    66
		push    350
		mov     ecx, resedit_edit
		mov     edx, [ecx]
		call    dword ptr [edx + 1Ch]
		mov     ecx, [esi + 0A74h]
		mov     eax, 004EC167h
		jmp     eax
	}
}

__declspec(naked) void something1() //004EFC3C
{
	__asm
	{
		mov     ecx, resedit_text
		push    esi
		mov     edx, [ecx]
		call    dword ptr [edx + 14h]
		mov     ecx, resedit_edit
		push    esi
		mov     edx, [ecx]
		call    dword ptr [edx + 14h]
		mov     ecx, [ebp + 0A78h]
		mov     eax, 004EFC42h
		jmp     eax
	}
}

__declspec(naked) void something2() //004DFA74
{
	__asm
	{
		mov     ecx, resedit_text
		push    edi
		mov     edx, [ecx]
		call    dword ptr [edx + 14h]
		mov     ecx, resedit_edit
		push    edi
		mov     edx, [ecx]
		call    dword ptr [edx + 14h]
		mov     ecx, [esi + 0A78h]
		mov     eax, 004DFA7Ah
		jmp     eax
	}
}

__declspec(naked) void editbox_1() //004E9115
{
	__asm
	{
		mov     ecx, resedit_edit
		push    1
		push    30608			//tooltip
		mov     eax, 00562D10h
		call    eax
		mov     ecx, [esi + 0A5Ch]
		mov     eax, 004E911Bh
		jmp     eax
	}
}

void __stdcall make_edit(void* this_, void** boxes, int count)
{
	__asm
	{
		mov     ecx, this_
		mov     edx, count
		mov     eax, boxes
		push    edx
		push    eax
		mov     edx, [ecx]
		call    dword ptr[edx + 0D8h]
	}
}

void __stdcall make_editboxes2(void** t)
{
	void* boxes[8];
	boxes[0] = t[662];
	boxes[1] = t[663];
	boxes[2] = t[664];
	boxes[3] = t[665];
	boxes[4] = t[666];
	boxes[5] = resedit_edit;
	boxes[6] = t[670];
	boxes[7] = t[679];
	make_edit(t, boxes, 8);
}

__declspec(naked) void make_editboxes() //004E933A
{
	__asm
	{
		push    esi
		call    make_editboxes2
		mov     eax, 004E9391h
		jmp     eax
	}
}

__declspec(naked) void sub_435BC0_oreX()
{
	__asm
	{
		mov     eax, [esp + 4]
		test    eax, eax
		jl      short locret_435BDB
		cmp     eax, 10h
		jge     short locret_435BDB
		mov     edx, [esp + 8]
		lea     eax, [eax + eax * 2]
		mov     [ecx + eax * 8 + 1A0Ch], edx
locret_435BDB:
		ret    8
	}
}

__declspec(naked) void res_set() //004F14C0
{
	__asm
	{
		mov     ecx, resedit_edit
		mov     eax, 0054DE40h
		call    eax
		push    eax
		mov     eax, 00614F6Bh
		call    eax
		add     esp, 4
		mov     [esp + 10h], eax
		push    eax
		mov     eax, [ebx + 0EC4h]
		push    ebp
		mov     ecx, [eax + 6Ch]
		call    sub_435BC0_oreX
		mov     edx, [ebx + 0EC4h]
		movsx   ecx, word ptr [ebx + 8FCh]
		fild    [esp + 10h]
		mov     eax, [edx + 4Ch]
		mov     ecx, [eax + ecx * 4]
		mov     edx, [ecx + 0A8h]
		fstp    dword ptr [edx]

		mov     ecx, [ebx + 0A58h]
		mov     eax, 004F14C6h
		jmp     eax
	}
}

__declspec(naked) void res_get() //004F17D5
{
	__asm
	{
		mov     ecx, [ebx + 0EC4h]
		push    esi
		mov     ecx, [ecx + 6Ch]
		mov     eax, 00435FA0h
		call    eax //getres_oreX
		push    eax
		lea     edx, [esp + 18h]
		push    0066B0E4h //"%d"
		push    edx
		mov     eax, 0061442Bh
		call    eax
		mov     ecx, resedit_edit
		add     esp, 0Ch
		lea     eax, [esp + 14h]
		push    eax
		mov     eax, 0054DCC0h
		call    eax
		mov     ecx, [ebx + 0EC4h]
		mov     eax, 004F17DBh
		jmp     eax
	}
}

//cheat
//00443F46


void set5thResHooks()
{
	setHook((void*)0x004E9024, create_text);
	setHook((void*)0x004E9103, create_edit);
	setHook((void*)0x004EEFD9, edit_delete);
	setHook((void*)0x004EC161, setrect);
	setHook((void*)0x004EFC3C, something1);
	setHook((void*)0x004DFA74, something2);
	setHook((void*)0x004E9115, editbox_1);
	setHook((void*)0x004E933A, make_editboxes);
	setHook((void*)0x004F14C0, res_set);
	setHook((void*)0x004F17D5, res_get);
}
