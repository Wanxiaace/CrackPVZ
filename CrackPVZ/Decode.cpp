#include "Decode.h"
#include "Definitions.h"

static unsigned int PVZfread(
	void* _Buffer,
	size_t _ElementSize,
	size_t _ElementCount,
	FILE* _Stream
) {
	unsigned int result = 0;

	lpFunc freadFunc = 0x61D24E;

	__asm {
		push _Stream
		push _ElementCount
		push _ElementSize
		push _Buffer
		call freadFunc
		mov result, eax
		add esp, 0x10
	}
	return result;
};

namespace PVZPakInterface {
	/// @brief PAK解码接口,实现自定义的PAK解码,若文件来自PAK,会对大小为theElemSize * theCount的内存进行解码
	/// @param thePtr 将要被写入的地址(缓冲区)
	/// @param theElemSize 元素大小
	/// @param theCount 元素个数
	/// @param theFile 文件信息,若theFile->mRecord不等于NULL,则该资源来自pak
	unsigned int _stdcall FRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile)
	{
		if (theFile->mRecord != NULL)
		{
			int aSizeBytes = min(theElemSize * theCount, theFile->mRecord->mSize - theFile->mPos);

			unsigned char* src = (unsigned char*)theFile->mRecord->mCollection->mDataPtr + theFile->mRecord->mStartPos + theFile->mPos;
			unsigned char* dest = (unsigned char*)thePtr;
			for (int i = 0; i < aSizeBytes; i++)
				*(dest++) = (*src++) ^ 0xF7; // 'Decrypt'
			theFile->mPos += aSizeBytes;
			return aSizeBytes / theElemSize;
		}

		return PVZfread(thePtr, theElemSize, theCount, theFile->mFP);
	}
}


