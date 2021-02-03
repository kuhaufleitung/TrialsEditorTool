#include "ProfileID.h"

void CProfileID::mSetUbiID (std::string EditorPath) {
	std::string Name = "";
	std::string NeededSubstring = "-0-0000000000000";
	
	hFind = FindFirstFileA((LPCSTR)(EditorPath + "\\*").c_str(), &data);
	Name = data.cFileName;


	while (Name.find(NeededSubstring) == std::string::npos) {
		FindNextFileA(hFind, &data);
		Name = data.cFileName;
	}
	FindClose(hFind);

	Name.resize(32);
	UbisoftID = Name;
	
}



std::string CProfileID::mUseUbiID() {
	return UbisoftID;
}