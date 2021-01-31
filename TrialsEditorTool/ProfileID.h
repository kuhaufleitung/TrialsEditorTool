#pragma once
#include <string>
#include <vector>
#include<Windows.h>

class CProfileID {
public:

	std::string mGetUbiID (std::string UbiString);
	void mRearrangeID();
	std::string mGetProfileID();



private:

	std::string UbisoftID;
	std::string SplitID[7];
	std::string ProfileID;

	HANDLE hFind;
	WIN32_FIND_DATAA data;
};