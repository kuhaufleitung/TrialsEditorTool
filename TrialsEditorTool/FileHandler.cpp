#include "FileHandler.h"
#include "PathHandler.h"


void CFileHandle::GetFirstFile(LPCSTR input) {
	LPCSTR addfix = "\\*";
	LPCSTR test = "C:\\Users\\FabiWindows\\Documents\\TrialsFusion\\SavedGames\\test\\*";
	std::string(test).append(addfix).c_str();
	hmFind = FindFirstFileA(test, &FileAttributes);
	while ((*FileAttributes.cFileName == '.') || (*FileAttributes.cFileName == '..') ||(FILE_ATTRIBUTE_DIRECTORY)) {
		FindNextFileA(hmFind, &FileAttributes);
	}
}


void CFileHandle::Init() {
	CPathHandle Path;
	Path.mPathDefaults();
	GetFirstFile(Path.mGetEditorPath().c_str());
}
