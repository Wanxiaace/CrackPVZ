#include <iostream>
#include "InlineHook.h"
#include "Decode.h"

namespace Helper {
	void HelperEntryPoint()
	{
		Hook::ReDirect((LPVOID)0x5D8850, PVZPakInterface::FRead);
	}
}
