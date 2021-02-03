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

	std::string mUseEditorPath();

	bool isConfigFileCreated;



private:

	std::fstream CfgFile;
	std::string const PathName = "Path.cfg";
	std::string EditorPath;

	char* docdir = getenv("USERPROFILE"); //path to Documents folder
};