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
	void mSetUbiPathVariable();

	std::string mUseEditorPath();
	std::string mUseUbiPath();

private:
	std::fstream CfgFile;
	std::string const PathName = "Path.cfg";
	std::string EditorPath;
	std::string UbiPath;

	char* docdir = getenv("USERPROFILE"); //path to Documents folder
};