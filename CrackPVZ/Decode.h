#ifndef __CRACK_DECODE_H__
#define __CRACK_DECODE_H__

#include "PakInterface.h"

namespace PVZPakInterface {
	unsigned int _stdcall FRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile);
}

#endif // !__CRACK_DECODE_H__
