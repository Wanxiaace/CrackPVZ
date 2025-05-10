#include "InlineHook.h"
#include "HelperMemory.hpp"
#include "AsmFunctions.h"

namespace Helper::Hook{
	void InlineHook(LPVOID addr, unsigned int fixSize, void (HOOK_CALL* hookFunc)(RegisterGrop))
	{
		if (fixSize < 5)
			return;
		unsigned char* data = new unsigned char[fixSize];
		Memory::ReadArray<unsigned char>(addr, data, fixSize);

		char* npData = new char[fixSize];
		memset(npData, NOP, fixSize);
		Memory::WriteArray<char>(addr, npData, fixSize);
		delete[] npData;

		Memory::WriteMemory<unsigned char>(addr, 0xE9);//≥§Ã¯
		LPVOID newmem = Memory::AllocMemory(0x40);
		memset(newmem, NOP, 0x40);

		//≈–∂œ «∑ÒHook¡ÀJMP
		if (data[0] == 0xE9 || data[0] == 0xE8) {//00413059
			*((unsigned int*)&data[1]) -= (0x15 + (unsigned int)newmem - (unsigned int)addr);
		}

		Memory::WriteMemory<unsigned int>(LPVOID((unsigned int)addr + 1), (unsigned int)newmem - (unsigned int)addr - 5);
		Memory::WriteArray(LPVOID((unsigned int)newmem + 0x15), data, fixSize);
		int jpl = (unsigned int)addr + fixSize - ((unsigned int)newmem + 0x15 + fixSize + 5);
		unsigned char jumpBack[] = { JMPFAR(jpl), };
		Memory::WriteArray<unsigned char>(LPVOID((unsigned int)newmem + 0x15 + fixSize), jumpBack, 5);

		unsigned char asmHookInterface[] = {
		PUSHAD,
		PUSHAD,
		MOV_EAX((int)hookFunc),
		CALL_EUX(REG_EAX),
		ADD_ESP(0x20),
		POPAD,
		};

		Memory::WriteArray<unsigned char>(newmem, asmHookInterface, sizeof(asmHookInterface));
	}
	
	void ReDirect(LPVOID addr, LPVOID redirectFunc)
	{
		unsigned char jumpFunc[] = {
			ADD_EUX(REG_ESP,0),
			MOV_EDX((unsigned int)redirectFunc),
			0xFF,0xE2//JMP EDX
		};

		Memory::WriteArray(addr, jumpFunc, sizeof(jumpFunc));
	}
}
