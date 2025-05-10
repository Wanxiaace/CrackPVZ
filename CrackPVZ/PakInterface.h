#ifndef __PAKINTERFACE_H__
#define __PAKINTERFACE_H__

#include <map>
#include <list>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class PakCollection;

struct PVZString {
#ifndef _DEBUG
	char mAlignment[4];
#endif // !_DEBUG
	std::string mString;
};

class PakRecord
{
public:
	PakCollection* mCollection;
	PVZString				mFileName;
	FILETIME				mFileTime;
	int						mStartPos;
	int						mSize;
};

class PakCollection
{
public:
	HANDLE					mFileHandle;
	HANDLE					mMappingHandle;
	void* mDataPtr;
};

struct PFILE
{
	PakRecord* mRecord;
	int						mPos;
	FILE* mFP;
};

struct PFindData
{
	HANDLE					mWHandle;
	PVZString				mLastFind;
	PVZString				mFindCriteria;
};

#endif //__PAKINTERFACE_H__
