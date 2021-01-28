#pragma once
#include <fstream>
#include <string>
#include <Windows.h>

class CCopy {
public:
	std::string mGetTemplatePath(std::string input);

private:
	std::string mTemplateFolder;

	//std::fstream TemplateMetadata;
	//std::fstream TemplateDisplayname;
	
	HANDLE hFindTemp;
	WIN32_FIND_DATAA data;

};