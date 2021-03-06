#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <windows.h>

class CPathHandle {
public:

	bool mPathDefaults();
	bool mCfgFound(const char* filename);

	void mSetEditorPathVariable();
	void mSetUbiID();

	std::string mGetEditorPath();
	std::string mGetUbiID();

	bool isConfigFileCreated;


private:

	std::fstream CfgFile;
	std::string const PathName = "Path.cfg";
	std::string EditorPath;
	std::string UbisoftID;

	HANDLE hFind;
	WIN32_FIND_DATAA data;

	char* docdir = getenv("USERPROFILE"); //path to Documents folder
};