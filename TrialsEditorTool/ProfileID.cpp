#include "ProfileID.h"

std::string CProfileID::mGetProfileID (std::string UbiString) {
	hFind = FindFirstFileA((LPCSTR)(UbiString + "\\*").c_str(), &data);
	while ((*data.cFileName == '.') || (*data.cFileName == '..')) {
		FindNextFileA(hFind, &data);
	}
	FindClose(hFind);
	return ProfileID = data.cFileName;
	
}

//Rearranges the ProfileID to suit the EditorFolder format
void CProfileID::mRearrangeID() {
	ArrangedBits[0] = ProfileID.substr(0, 8);
	ArrangedBits[1] = ProfileID.substr(9, 4);
	ArrangedBits[2] = ProfileID.substr(14, 4);
	ArrangedBits[3] = ProfileID.substr(19, 4);
	ArrangedBits[4] = ProfileID.substr(24, 4);
	ArrangedBits[5] = ProfileID.substr(28, 4);
	ArrangedBits[6] = ProfileID.substr(32, 4);
	SortedID = ArrangedBits[2];
	SortedID.append(ArrangedBits[1]);
	SortedID.append(ArrangedBits[0]);
	SortedID.append(ArrangedBits[6]);
	SortedID.append(ArrangedBits[5]);
	SortedID.append(ArrangedBits[4]);
	SortedID.append(ArrangedBits[3]);
	}