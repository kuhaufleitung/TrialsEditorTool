#include "PathHandler.h"


bool CPathHandle::mCfgFound(const char* filename)
{
	std::ifstream infile(filename);
	return infile.good();
}



bool CPathHandle::mPathDefaults() {

	
	if (mCfgFound("Path.cfg") == false) {


		CfgFile.open(PathName, std::fstream::out);
		CfgFile << docdir << "\\Documents\\TrialsFusion\\SavedGames" << std::endl << std::endl;

		CfgFile << "//The path looks like this structure and points to your Trials SavedGames Directory:\n//C:\\Users\\*yourname*\\Documents\\TrialsFusion\\SavedGames" << std::endl << std::endl
				<< "//There have to be NO backslashes at the end!" << std::endl
				<< "//This file gets auto generated when it isnt available in the program directory." << std::endl << std::endl
				<< "//TrialsEditorTool by kuhaufleitung";
		
		CfgFile.close();
	}
	else { isConfigFileCreated = true; };
	
	return isConfigFileCreated;
}



void CPathHandle::mSetEditorPathVariable() {

	std::stringstream FileStream;

	CfgFile.open(PathName);
	FileStream << CfgFile.rdbuf();
	std::getline(FileStream, EditorPath);
	CfgFile.close();

}



void CPathHandle::mSetUbiID() {
	std::string Name = "";
	std::string NeededSubstring = "-0-0000000000000";

	hFind = FindFirstFileA((LPCSTR)(EditorPath + "\\*").c_str(), &data);
	Name = data.cFileName;


	while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {
		if (Name.find(NeededSubstring) != std::string::npos) {
			
			foundTrack = true;
			Name.resize(32);
			UbisoftID = Name;

		}
		FindNextFileA(hFind, &data);
		Name = data.cFileName;
	}
	
	//reset error so it isnt ERROR_NO_MORE_FILES as this is used again when creating the TrackArray
	SetLastError(0);
	FindClose(hFind);

}



std::string CPathHandle::mGetUbiID() {
	return UbisoftID;
}

std::string CPathHandle::mGetEditorPath() {
	return EditorPath;
}
