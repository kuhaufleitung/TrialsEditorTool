#pragma once
#include <Windows.h>
#include "PathHandler.h"
#include <string>
#include <vector>


class CFileHandle {
public:
	void Init(std::string classstring);
	void mGetFirstFile(std::string input);
	void mGetNextFiles();
	//INT_PTR CALLBACK ListBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


	std::vector<std::string> TrackID;

private:
	CPathHandle* Path;
	HANDLE hFind;
	WIN32_FIND_DATAA FileAttributes;

};