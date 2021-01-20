#pragma once
#include <Windows.h>
#include "PathHandler.h"
#include <string>

class CFileHandle {
public:
	void Init();
	void SetDirectory(CPathHandle* input);
	void GetFirstFile(CPathHandle temp);
private:
	CPathHandle* Path;
	HANDLE hmFind;
	WIN32_FIND_DATAA FileAttributes;
};