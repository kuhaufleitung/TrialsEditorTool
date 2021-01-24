#include "FileHandler.h"
#include "PathHandler.h"


void CFileHandle::GetFirstFile(std::string input) {

	hmFind = FindFirstFileA((LPCSTR)(input + "\\*").c_str(), &FileAttributes); //handle returns first file

	while ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '.')) {
		FindNextFileA(hmFind, &FileAttributes);
	}
}


void CFileHandle::Init() {
	CPathHandle Path;
	Path.mPathDefaults();
	GetFirstFile(Path.mGetEditorPath().c_str());
}
