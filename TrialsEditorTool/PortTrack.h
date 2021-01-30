#pragma once
#include <string>
#include <Windows.h>

class CPort {
public:
	std::string mGetTemplatePath(std::string input, std::string ProfileID);
	std::string mUseTemplatePath();
	void mCreateFolder(std::string EditorPath, std::string ProfileID, std::string Unix);
private:

	std::string TemplateFolder;


	HANDLE hFindTemplate;
	WIN32_FIND_DATAA data;
	LPSECURITY_ATTRIBUTES sec;
};