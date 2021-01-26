#pragma once
#include <Windows.h>
#include "PathHandler.h"
#include <string>
#include <vector>


class CFileHandle {
public:
	void Init();
	void mGetFirstFile(std::string input);
	void mGetNextFiles();

private:
	CPathHandle* Path;
	HANDLE hFind;
	WIN32_FIND_DATAA FileAttributes;
	std::vector<std::string> mTrackID;

};