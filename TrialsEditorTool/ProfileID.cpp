#include "ProfileID.h"

std::string CProfileID::mGetUbiID (std::string UbiString) {
	hFind = FindFirstFileA((LPCSTR)(UbiString + "\\*").c_str(), &data);
	while ((*data.cFileName == '.') || (*data.cFileName == '..')) {
		FindNextFileA(hFind, &data);
	}
	FindClose(hFind);
	return UbisoftID = data.cFileName;
	
}

//Rearranges the ProfileID to suit the EditorFolder format
void CProfileID::mRearrangeID() {
	SplitID[0] = UbisoftID.substr(0, 8);
	SplitID[1] = UbisoftID.substr(9, 4);
	SplitID[2] = UbisoftID.substr(14, 4);
	SplitID[3] = UbisoftID.substr(19, 4);
	SplitID[4] = UbisoftID.substr(24, 4);
	SplitID[5] = UbisoftID.substr(28, 4);
	SplitID[6] = UbisoftID.substr(32, 4);
	//splitted ID into array

	//sort everything
	ProfileID = SplitID[2];
	ProfileID.append(SplitID[1]);
	ProfileID.append(SplitID[0]);
	ProfileID.append(SplitID[6]);
	ProfileID.append(SplitID[5]);
	ProfileID.append(SplitID[4]);
	ProfileID.append(SplitID[3]);
	}

std::string CProfileID::mGetProfileID() {
	return ProfileID;
}