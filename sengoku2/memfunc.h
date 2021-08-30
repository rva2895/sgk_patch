#pragma once

void __cdecl setByte(DWORD addr, BYTE val);
void __cdecl setInt(DWORD addr, DWORD val);
void __cdecl setByteF(DWORD addr, BYTE val);
void __cdecl setIntF(DWORD addr, DWORD val);
void __cdecl setHook(void* addr, void* newAddr);
//void __cdecl setHookRestorable (void* addr, void* newAddr, void* oldData);
//void __cdecl restoreHook (void* addr, void* oldData);

//int __cdecl readInt (int addr);

int __stdcall getWindowX();
int __stdcall getWindowY();

struct BYTE_ASSIGN
{
	DWORD  addr;
	BYTE val;
};

struct INT_ASSIGN
{
	DWORD  addr;
	DWORD  val;
};

struct SET_HOOK_ASSIGN
{
	void* addr;
	void* newAddr;
};

void __stdcall sendChat(char* s, int p);
void __cdecl chat(char* format, ...);
