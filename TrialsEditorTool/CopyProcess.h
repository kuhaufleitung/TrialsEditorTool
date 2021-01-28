#pragma once
#include <fstream>
#include <string>
#include <Windows.h>

class CCopy {
public:
	std::string GetTemplatePath(std::string input);
	std::string TemplateFolder;

private:
	std::fstream TemplateMetadata;
	std::fstream TemplateDisplayname;
	
	HANDLE hFindTemp;
	WIN32_FIND_DATAA data;

};