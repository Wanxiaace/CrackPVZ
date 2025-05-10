#ifndef __HELPER_MEMORY_H__
#define __HELPER_MEMORY_H__

#include "Definitions.h"

#define PAGE_SIZE 1024

/*
* ²¿·Ö²Î¿¼PVZClass£¨ÀÁ£©
*/

namespace Helper::Memory {
	static bool AccessAll(LPVOID address) {
		DWORD op = PAGE_READONLY;
		return VirtualProtect(address, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &op);
	}

	static LPVOID AllocMemory(unsigned int size) {
		LPVOID page = new char[size];
		return page;
	}

	static LPVOID PVZNew(int _size) {
		LPVOID re = 0;
		lpFunc newFunc = 0x61C130;
		__asm {
			push _size
			call newFunc
			mov re, eax
			add esp, 0x4
		}
		return re;
	}

	static void PVZDelete(void* _mem)
	{
		lpFunc deleteFunc = 0x61C19A;
		__asm {
			push _mem
			call deleteFunc
			add esp, 0x4
		}
	}

	template <class T>
	inline static T ReadMemory(int address)
	{
		T* buffer = (T*)address;
		return *buffer;
	};

	template <class T>
	inline static void WriteMemory(LPVOID address, T value)
	{
		AccessAll(address);
		T* buffer = (T*)address;
		*buffer = value;
	};

	template <class T>
	inline static void ReadArray(LPCVOID address, T* result, size_t length)
	{
		memcpy(result, address, length);
	};

	template <class T>
	inline static void WriteArray(LPVOID address, T* value, size_t length)
	{
		AccessAll(address);
		memcpy(address, value, length);
	};

	class Pointer {
	public:
		void* mValue;

	public:
		Pointer Offset(unsigned int offset);
	};

	Pointer ReadPointer(LPVOID address);
}

#endif // !__HELPER_MEMORY_H__
