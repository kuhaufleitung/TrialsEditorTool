#include "PortTrack.h"

std::string CPort::mGetTemplatePath(std::string input, std::string ProfileID) {

	hFindTemplate = FindFirstFileA((LPCSTR)(input + "//*").c_str(), &data);
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
