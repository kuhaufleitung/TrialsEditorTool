#include "PortTrack.h"

std::string CPort::mGetTemplatePath(std::string input) {

	hFindTemplate = FindFirstFileA((LPCSTR)(input + "//*").c_str(), &data);
	mTemplateFolder = data.cFileName;

	while (mTemplateFolder.find("0000000000000") == std::string::npos) {
		FindNextFileA(hFindTemp, &data);
		mTemplateFolder = data.cFileName;
	}
	FindClose(hFindTemp);
	return mTemplateFolder;
}
