#include "PathHandler.h"


bool CPathHandle::mCfgFound(const char* filename)
{
	std::ifstream infile(filename);
	return infile.good();
}



bool CPathHandle::mPathDefaults() {

	
	if (mCfgFound("Path.cfg") == false) {


		CfgFile.open(PathName, std::fstream::out);
		CfgFile << docdir << "\\Documents\\Ubisoft\\Trials Evolution Gold Edition\\SavedGames" << std::endl;
		CfgFile << docdir << "\\Documents\\TrialsFusion\\SavedGames" << std::endl;
		//TODO: get Rising UserID in Path and CacheStorage/usertracks or only usertracks?
		CfgFile << docdir << "\\Documents\\Trials Rising\\SavedGames\\ID\\" << std::endl << std::endl << std::endl;


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
		}
	}


	CfgFile.close();

}



void CPathHandle::mSetUbiID(Game::GameSel Game) {
	
	std::string Name = "";
	std::string NeededSubstring = "-0-0000000000000";

	if (Game == Game::GameSel::Evo || Game == Game::GameSel::Fusion) {

		hFind = FindFirstFileA((LPCSTR)(EditorPath + "\\*").c_str(), &data);
		Name = data.cFileName;


		while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {
			if (Name.find(NeededSubstring) != std::string::npos) {

				foundTrack = true;
				if (Game == Game::GameSel::Evo) {
					Name.resize(19);
				}
				else if (Game == Game::GameSel::Fusion) {
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

	} //Rising only needs copying, so no need to do that

}



std::string CPathHandle::mGetUbiID() {
	return UbisoftID;
}

void CPathHandle::mSetEditorPath(Game::GameSel Game) {
	switch (Game) {
		case Game::GameSel::Evo:
		{
			EditorPath = EditorPathEvo;
		}break;
		case Game::GameSel::Fusion:
		{
			EditorPath = EditorPathFusion;
		}break;
		case Game::GameSel::Rising:
		{
			EditorPath = EditorPathRising;
		}break;
	}
}

std::string CPathHandle::mGetEditorPath() {
	return EditorPath;
}