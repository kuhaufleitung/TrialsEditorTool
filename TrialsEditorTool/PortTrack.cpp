#include "PortTrack.h"

std::string CPort::mGetTemplatePath(std::string input) {

	hFindTemplate = FindFirstFileA((LPCSTR)(input + "//*").c_str(), &data);
	TemplateFolder = data.cFileName;

	while (TemplateFolder.find("0000000000000") == std::string::npos) {
		FindNextFileA(hFindTemplate, &data);
		TemplateFolder = data.cFileName;
	}
	FindClose(hFindTemplate);
	return TemplateFolder;
}
