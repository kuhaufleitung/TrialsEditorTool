#include "CopyProcess.h"

std::string CCopy::GetTemplatePath(std::string input) {

	hFindTemp = FindFirstFileA((LPCSTR)(input + "//*").c_str(), &data);
	TemplateFolder = data.cFileName;

	while (TemplateFolder.find("0000000000000") == std::string::npos) {
		FindNextFileA(hFindTemp, &data);
		TemplateFolder = data.cFileName;
	}
	FindClose(hFindTemp);
	return TemplateFolder;
}