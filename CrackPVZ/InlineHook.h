#ifndef __HELPER_INLINE_HOOK_H__
#define __HELPER_INLINE_HOOK_H__

#include "Definitions.h"
#include <functional>

#define HOOK_CALL __cdecl

namespace Helper::Hook {
	/// @param addr
	/// @param fixSize
	/// @param hookFunc
	/// @brief �򵥵�inlinehook,����fixSize����ת��Ĵ�С
	/// @note ������__cdeclԼ���ĺ���(HOOK_CALL��)
	void InlineHook(LPVOID addr, unsigned int fixSize, void (HOOK_CALL* hookFunc)(RegisterGrop));

	void ReDirect(LPVOID addr, LPVOID redirectFunc);

}

#endif // !__HELPER_INLINE_HOOK_H__
