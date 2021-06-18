#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "enum.h"

class CPort {
public:

	std::string mSetTemplatePath(std::string input, std::string ProfileID);
	std::string mGetTemplatePath();

	void mCreateFolder(std::string EditorPath, std::string ProfileID, std::string Unix);
	void mCopyNameMDA(std::string EditorPath, std::string ExistingTrackID);
	void mModifyTrkfile(std::string EditorPath, std::string ExistingTrackID, Selection::Game Game);



private:

	std::string TemplateFolder;
	std::string NewTrackFolder;

	HANDLE hFindTemplate = nullptr;
	WIN32_FIND_DATAA data;
	LPSECURITY_ATTRIBUTES sec = nullptr;

	std::ifstream OriginalTrack;
	std::ifstream TemplateTrack;
	std::ofstream NewTrack;
};