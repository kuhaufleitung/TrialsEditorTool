#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

class CPathHandle {
public:
	void mPathDefaults();
	bool mCfgFound(const char* filename);

	void mSetEditorPathVariable();
	std::string mUseEditorPath();
	std::string mGetUbiPath();

private:
	std::fstream CfgFile;
	std::string const PathName = "Path.cfg";
	std::string EditorPath;
	std::string UbiPath;

	char* docdir = getenv("USERPROFILE"); //path to Documents folder
};