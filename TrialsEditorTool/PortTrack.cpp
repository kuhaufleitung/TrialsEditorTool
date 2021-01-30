#include "PortTrack.h"

std::string CPort::mGetTemplatePath(std::string input, std::string ProfileID) {

	hFindTemplate = FindFirstFileA((LPCSTR)(input + "\\*").c_str(), &data);
	TemplateFolder = data.cFileName;

	while (TemplateFolder.find(ProfileID) == std::string::npos) {
		FindNextFileA(hFindTemplate, &data);
		TemplateFolder = data.cFileName;
	}
	FindClose(hFindTemplate);
	return TemplateFolder;
}

std::string CPort::mUseTemplatePath() {
	return TemplateFolder;
}

//UbiID UNIXTIMESTAMP -0-0000000000000 (no spaces)
void CPort::mCreateFolder(std::string EditorPath, std::string ProfileID, std::string Unix) {


	NewTrackFolder = EditorPath + "\\" + ProfileID + Unix + "-0-0000000000000"; //for copying process

	CreateDirectoryA((LPCSTR) NewTrackFolder.c_str(), sec);
}


void CPort::mCopyNameMDA(std::string EditorPath, std::string ExistingTrackID) {
	
	//Copy displayname
	std::string ExistingTrackPath = EditorPath + "\\" + ExistingTrackID;
	
	BOOL failD = CopyFileA((LPCSTR)(ExistingTrackPath + "\\displayname").c_str(), (LPCSTR)(NewTrackFolder + "\\displayname").c_str(), 0);
	if (!failD) {
		DWORD error = GetLastError();
	}

	
	//Copy metadata.mda
	std::string ExistingTemplatePath = EditorPath + "\\" + TemplateFolder;

	BOOL failM = CopyFileA((LPCSTR)(ExistingTemplatePath + "\\metadata.mda").c_str(), (LPCSTR)(NewTrackFolder + "\\metadata.mda").c_str(), 0);
	if (!failM) {
		DWORD error = GetLastError();
	}

}
