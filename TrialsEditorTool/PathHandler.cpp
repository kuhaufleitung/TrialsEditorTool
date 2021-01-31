#include "PathHandler.h"
namespace fs = std::filesystem;

//checks Path.cfg access
bool CPathHandle::mCfgFound(const char* filename)
{
	std::ifstream infile(filename);
	return infile.good();
}



//opens cfg and writes StdPath if not created
bool CPathHandle::mPathDefaults() {

	
	if (mCfgFound("Path.cfg") == false) {

		isConfigFileCreated = false;

		CfgFile.open(PathName, std::fstream::out);
		CfgFile << docdir << "\\Documents\\TrialsFusion\\SavedGames" << std::endl;
		CfgFile << "C:\\Program Files (x86)\\Ubisoft\\Ubisoft Game Launcher" << std::endl << std::endl;

		CfgFile << "//FirstPath looks like this structure and points to your Trials SavedGames Directory:\n//C:\\Users\\*yourname*\\Documents\\TrialsFusion\\SavedGames" << std::endl << std::endl
				<< "//SecondPath looks like this structure and points to your Ubisoft Game Launcher Directory, NOT your game:\n//C:\\Program Files (x86)\\Ubisoft\\Ubisoft Game Launcher" << std::endl << std::endl
				<< "//There have to be NO backslashes at the end!" << std::endl
				<< "//This file gets auto generated when it isnt available in the program directory.";
		
		CfgFile.close();
	}
	else { isConfigFileCreated = true; };
	
	return isConfigFileCreated;
}



//reads file to EditorPath sstream and returns its content
void CPathHandle::mSetEditorPathVariable() {

	std::stringstream FileStream;

	CfgFile.open(PathName);
	FileStream << CfgFile.rdbuf();
	std::getline(FileStream, EditorPath);
	CfgFile.close();

}



//reads file to UbiPath sstream and returns its content
void CPathHandle::mSetUbiPathVariable() {

	std::stringstream FileStream;

	CfgFile.open(PathName);

	FileStream << CfgFile.rdbuf();
	std::getline(FileStream, UbiPath);
	std::getline(FileStream, UbiPath); //unpretty but who cares.

	//we need the savegames folder for the ID
	UbiPath.append("\\savegames");
	CfgFile.close();
}

std::string CPathHandle::mUseEditorPath() {
	return EditorPath;
}

std::string CPathHandle::mUseUbiPath() {
	return UbiPath;
}