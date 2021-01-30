#include "PathHandler.h"
namespace fs = std::filesystem;

//checks Path.cfg access
bool CPathHandle::mCfgFound(const char* filename)
{
	std::ifstream infile(filename);
	return infile.good();
}


//opens cfg and writes StdPath if not created
void CPathHandle::mPathDefaults() {

	if (mCfgFound("Path.cfg") == false) {
		CfgFile.open(PathName, std::fstream::out);
		CfgFile << docdir << "\\Documents\\TrialsFusion\\SavedGames" << std::endl;
		CfgFile << "C:\\Program Files (x86)\\Ubisoft\\Ubisoft Game Launcher\\savegames";
	}
	CfgFile.close();
}


//reads file to EditorPath sstream and returns its content
std::string CPathHandle::mGetEditorPath() {

	std::stringstream FileStream;

	CfgFile.open(PathName);
	FileStream << CfgFile.rdbuf();
	std::getline(FileStream, EditorPath);
	CfgFile.close();

	return EditorPath;
}

//reads file to UbiPath sstream and returns its content
std::string CPathHandle::mGetUbiPath() {

	std::stringstream FileStream;

	CfgFile.open(PathName);

	FileStream << CfgFile.rdbuf();
	std::getline(FileStream, UbiPath);
	std::getline(FileStream, UbiPath); //unpretty but who cares.

	CfgFile.close();
	return UbiPath;
}
