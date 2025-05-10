#ifndef __HELPER_INLINE_HOOK_H__
#define __HELPER_INLINE_HOOK_H__

#include "Definitions.h"
#include <functional>

#define HOOK_CALL __cdecl

namespace Helper::Hook {
	/// @param addr
	/// @param fixSize
	/// @param hookFunc
	/// @brief 简单的inlinehook,其中fixSize是跳转块的大小
	/// @note 必须以__cdecl约定的函数(HOOK_CALL宏)
	void InlineHook(LPVOID addr, unsigned int fixSize, void (HOOK_CALL* hookFunc)(RegisterGrop));

	void ReDirect(LPVOID addr, LPVOID redirectFunc);

}

#endif // !__HELPER_INLINE_HOOK_H__
