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

//446ebf93f535b37276d4afbbbfd38a882642e85d02-0-0000000000000
void CPort::mCreateFolder(std::string EditorPath, std::string ProfileID, std::string Unix) {
	CreateDirectoryA((LPCSTR) (EditorPath + "\\" + ProfileID + Unix).c_str(), sec);
}