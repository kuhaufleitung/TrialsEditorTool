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
		CfgFile << docdir << "\\Documents\\TrialsFusion\\SavedGames" << std::endl << std::endl;

		CfgFile << "//FirstPath looks like this structure and points to your Trials SavedGames Directory:\n//C:\\Users\\*yourname*\\Documents\\TrialsFusion\\SavedGames" << std::endl << std::endl
				<< "//There have to be NO backslashes at the end!" << std::endl
				<< "//This file gets auto generated when it isnt available in the program directory." << std::endl << std::endl
				<< "//TrialsEditorTool by kuhaufleitung";
		
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



std::string CPathHandle::mUseEditorPath() {
	return EditorPath;
}
