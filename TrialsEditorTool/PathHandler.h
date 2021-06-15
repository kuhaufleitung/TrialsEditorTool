#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <windows.h>
#include "enum.h"

class CPathHandle {
public:

	bool mPathDefaults();
	bool mCfgFound(const char* filename);

	void mRetrieveEditorPathVariables();
	void mSetUbiID(Game::GameSel Game);
	void mSetEditorPath(Game::GameSel Game);
	
	std::string mGetEditorPath();
	std::string mGetUbiID();

	bool isConfigFileCreated = false;
	bool foundTrack = false;

private:

	std::fstream CfgFile;
	std::string const PathName = "Path.cfg";
	std::string EditorPath;
	std::string EditorPathFusion;
	std::string EditorPathEvo;
	std::string EditorPathRising;
	std::string UbisoftID;

	HANDLE hFind = nullptr;
	WIN32_FIND_DATAA data;

	char* docdir = getenv("USERPROFILE"); //path to Documents folder
};