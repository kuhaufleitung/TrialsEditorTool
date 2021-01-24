#pragma once
#include <Windows.h>
#include "PathHandler.h"
#include <string>

class CFileHandle {
public:
	void Init();
	void GetFirstFile(LPCSTR input);
private:
	CPathHandle* Path;
	HANDLE hmFind;
	WIN32_FIND_DATAA FileAttributes;
};