#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

class CPathHandle {
public:
	//CPathHandle();
	void mPathDefaults();
	void mUbiSavegamePath();
	bool mCfgFound(const char* filename);

	std::string mGetEditorPath();
	std::string mGetUbiPath();

private:
	std::fstream CfgFile;
	std::string const PathName = "Path.cfg";
	std::string EditorPath;
	std::string UbiPath;
	std::stringstream FileStream;

	char* docdir = getenv("USERPROFILE"); //path to Documents folder
};