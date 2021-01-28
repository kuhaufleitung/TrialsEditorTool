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
	std::vector<std::string> TrackNames;

private:
	std::ifstream NameOpen;
	std::string buffer;

	HANDLE hFind;
	WIN32_FIND_DATAA FileAttributes;
};