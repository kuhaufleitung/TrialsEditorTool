#pragma once
#include <fstream>
#include <string>
#include <Windows.h>
#include "PathHandler.h"
#include "ProfileID.h"
#include "TrackArray.h"
#include "Resource.h"

class CCopy {
public:
	void mInitUI(HWND hWnd, HINSTANCE hInst);
	void mSetUI(HWND hWnd, HINSTANCE hInst);
	void mOnButtonClick(int i);
	std::string mGetTemplatePath(std::string input);
	

private:
	std::string mTemplateFolder;

	//std::fstream TemplateMetadata;
	//std::fstream TemplateDisplayname;
	
	CPathHandle Path;
	CTrackArray* File = new CTrackArray;
	CProfileID Profile;

	HWND hList;
	HWND hButton;
	HANDLE hFindTemp;
	WIN32_FIND_DATAA data;

};