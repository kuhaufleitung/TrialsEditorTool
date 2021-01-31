#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <Windows.h>

class CPort {
public:
	std::string mGetTemplatePath(std::string input, std::string ProfileID);
	std::string mUseTemplatePath();

	void mCreateFolder(std::string EditorPath, std::string ProfileID, std::string Unix);
	void mCopyNameMDA(std::string EditorPath, std::string ExistingTrackID);
	void mModifyTrkfile(std::string EditorPath, std::string ExistingTrackID);

private:

	std::string TemplateFolder;
	std::string NewTrackFolder;

	HANDLE hFindTemplate;
	WIN32_FIND_DATAA data;
	LPSECURITY_ATTRIBUTES sec;

	std::ifstream OriginalTrack;
	std::ifstream TemplateTrack;
	std::ofstream NewTrack;
};