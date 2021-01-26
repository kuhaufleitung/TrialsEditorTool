#pragma once
#include <string>
#include <vector>
#include<Windows.h>

class CProfileID {
public:
	std::string mGetProfileID (std::string UbiString);
	void mRearrangeID();

private:
	std::string ProfileID;
	std::string ArrangedBits[7];
	std::string SortedID;

	HANDLE hFind;
	WIN32_FIND_DATAA data;
};