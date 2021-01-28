#include "CopyProcess.h"

std::string CCopy::mGetTemplatePath(std::string input) {

	hFindTemp = FindFirstFileA((LPCSTR)(input + "//*").c_str(), &data);
	mTemplateFolder = data.cFileName;

	while (mTemplateFolder.find("0000000000000") == std::string::npos) {
		FindNextFileA(hFindTemp, &data);
		mTemplateFolder = data.cFileName;
	}
	FindClose(hFindTemp);
	return mTemplateFolder;
}