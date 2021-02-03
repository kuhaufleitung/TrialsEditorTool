#pragma once
#include <string>
#include <vector>
#include<Windows.h>

class CProfileID {
public:

	void mSetUbiID (std::string EditorPath);
	std::string mUseUbiID();

private:

	std::string UbisoftID;

	HANDLE hFind;
	WIN32_FIND_DATAA data;
};