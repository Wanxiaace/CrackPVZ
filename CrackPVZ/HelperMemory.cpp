#include "HelperMemory.hpp"


namespace Helper::Memory {

	Pointer Pointer::Offset(unsigned int offset)
	{
		return { ReadPointer(LPVOID(unsigned int(mValue) + offset)) };
	}

	Pointer ReadPointer(LPVOID address)
	{
		return { (void*)ReadMemory<unsigned int>((int)address) };
	}
}
