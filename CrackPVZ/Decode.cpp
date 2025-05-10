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
	/// @brief PAK����ӿ�,ʵ���Զ����PAK����,���ļ�����PAK,��Դ�СΪtheElemSize * theCount���ڴ���н���
	/// @param thePtr ��Ҫ��д��ĵ�ַ(������)
	/// @param theElemSize Ԫ�ش�С
	/// @param theCount Ԫ�ظ���
	/// @param theFile �ļ���Ϣ,��theFile->mRecord������NULL,�����Դ����pak
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


