#include "PathHandler.h"


bool CPathHandle::mCfgFound(const char* filename)
{
	std::ifstream infile(filename);
	return infile.good();
}



bool CPathHandle::mPathDefaults() {

	
	if (!mCfgFound("Path.cfg")) {


		CfgFile.open(PathName, std::fstream::out);
		CfgFile << docdir << "\\Documents\\Ubisoft\\Trials Evolution Gold Edition\\SavedGames" << std::endl;
		CfgFile << docdir << "\\Documents\\TrialsFusion\\SavedGames" << std::endl;
		CfgFile << docdir << "\\Documents\\Trials Rising\\SavedGames" << std::endl << std::endl << std::endl;


		CfgFile << "//The path looks like this structure and points to your Trials SavedGames Directory:\n//C:\\Users\\*yourname*\\Documents\\TrialsFusion\\SavedGames" << std::endl << std::endl
				<< "//There have to be NO backslashes at the end!" << std::endl
				<< "//This file gets auto generated when it isnt available in the program directory." << std::endl << std::endl
				<< "//TrialsEditorTool by kuhaufleitung";
		
		CfgFile.close();
	}
	else { isConfigFileCreated = true; };
	
	return isConfigFileCreated;
}



void CPathHandle::mRetrieveEditorPathVariables() {

	std::stringstream FileStream;
	std::string buffer;

	CfgFile.open(PathName);
	FileStream << CfgFile.rdbuf();

	for (int i = 0; i < 3; i++) {

		std::getline(FileStream, buffer);

		if (buffer.find("Evo") != std::string::npos) {
			EditorPathEvo = buffer;
		}
		else if (buffer.find("Fusion") != std::string::npos) {
			EditorPathFusion = buffer;
		}
		else if (buffer.find("Rising") != std::string::npos) {
			EditorPathRising = buffer;
			EditorPathRising += mSetRisingUserID();
		}
	}


	CfgFile.close();

}



void CPathHandle::mSetUbiID(Selection::Game Game) {
	
	std::string Name = "";
	std::string NeededSubstring = "-0-0000000000000";

	if (Game == Selection::Game::Evo || Game == Selection::Game::Fusion) {

		hFind = FindFirstFileA((LPCSTR)(EditorPath + "\\*").c_str(), &data);
		Name = data.cFileName;


		while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {
			if (Name.find(NeededSubstring) != std::string::npos) {

				foundTrack = true;
				if (Game == Selection::Game::Evo) {
					Name.resize(19);
				}
				else if (Game == Selection::Game::Fusion) {
					Name.resize(32);
				}
				UbisoftID = Name;
				break;
			}
			FindNextFileA(hFind, &data);
			Name = data.cFileName;

		}

		//reset error so it isnt ERROR_NO_MORE_FILES as this is used again when creating the TrackArray
		SetLastError(0);
		FindClose(hFind);
		hFind = nullptr;

	} else if (Game == Selection::Game::Rising) {
		
		//we force foundTrack = true, bc there is no need in checking for own tracks
		foundTrack = true;
	}

}



std::string CPathHandle::mSetRisingUserID() {
	
	std::string Name = "";
	
	hFind = FindFirstFileA((LPCSTR)(EditorPathRising + "\\*").c_str(), &data);
	Name = data.cFileName;

	while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {
		
		//FolderFormat: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx a-z,0-9
		if (std::regex_match (Name, std::regex("([a-z0-9]{8})\\-([a-z0-9]{4})\\-([a-z0-9]{4})\\-([a-z0-9]{4})\\-([a-z0-9]{12})"))) {
			RisingUserID = Name;
			break;
		}
		FindNextFileA(hFind, &data);
		Name = data.cFileName;
	}

	SetLastError(0);
	FindClose(hFind);
	hFind = nullptr;

	RisingUserID = "\\" + RisingUserID + "\\CacheStorage\\usertracks";

	return RisingUserID;
}



std::string CPathHandle::mGetUbiID() {
	return UbisoftID;
}



void CPathHandle::mSetEditorPath(Selection::Game Game) {
	switch (Game) {
		case Selection::Game::Evo:
		{
			EditorPath = EditorPathEvo;
		}break;
		case Selection::Game::Fusion:
		{
			EditorPath = EditorPathFusion;
		}break;
		case Selection::Game::Rising:
		{
			EditorPath = EditorPathRising;
		}break;
	}
}



std::string CPathHandle::mGetEditorPath() {
	return EditorPath;
}