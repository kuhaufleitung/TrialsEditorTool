#pragma once
#include <Windows.h>
#include <string>
#include <vector>


class CFileHandle {
public:
	void Init(std::string classstring);
	void mGetFirstFile(std::string input);
	void mGetNextFiles();

	std::vector<std::string> TrackID;

private:
	HANDLE hFind;
	WIN32_FIND_DATAA FileAttributes;
};