#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <windows.h>
#include "enum.h"
#include <regex>

class CPathHandle {
public:

	bool mPathDefaults();

	void mRetrieveEditorPathVariables();
	void mSetUbiID(Selection::Game Game);
	void mSetEditorPath(Selection::Game Game);

	std::string mGetEditorPath();
	std::string mGetUbiID();

	bool isConfigFileCreated = false;
	bool foundTrack = false;

private:

	bool mCfgFound(const char* filename);
	std::string mSetRisingUserID();

	std::fstream CfgFile;
	std::string const PathName = "Path.cfg";
	std::string EditorPath;
	std::string EditorPathFusion;
	std::string EditorPathEvo;
	std::string EditorPathRising;
	std::string UbisoftID;
	std::string RisingUserID;

	HANDLE hFind = nullptr;
	WIN32_FIND_DATAA data;

	char* docdir = getenv("USERPROFILE"); //path to Documents folder
};