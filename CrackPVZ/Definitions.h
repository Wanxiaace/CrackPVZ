#ifndef __HELPER_DEFINITIONS_H__
#define __HELPER_DEFINITIONS_H__

#include <Windows.h>

#define HELPER_VERSION "0.0"

using Register = int;
using lpFunc = unsigned int;

struct RegisterGrop {
	Register edi;
	Register esi;
	Register ebp;
	Register esp;
	Register ebx;
	Register edx;
	Register ecx;
	Register eax;
};

#define MSG_FATAL_ERROR_AND_ABORT(x) {MessageBoxA(NULL,x,"FATAL ERROR",NULL); abort();}

#endif // !__HELPER_DEFINITIONS_H__

