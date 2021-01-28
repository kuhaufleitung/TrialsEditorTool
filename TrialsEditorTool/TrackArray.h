#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class TrackArray {
public:
	void Init(std::string classstring);
	void mGetFirstFile(std::string input);
	void mGetNextFiles();

	void mGetTracknameList(std::string Path);
	//bool mNameFileFound(const char* filename);

	std::vector<std::string> TrackID;
	std::vector<std::wstring> TrackNames;

private:
	std::wifstream NameOpen;
	std::wstring buffer;

	HANDLE hFind;
	WIN32_FIND_DATAA FileAttributes;
};