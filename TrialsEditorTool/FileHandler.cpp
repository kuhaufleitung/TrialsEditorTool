#include "FileHandler.h"
#include "PathHandler.h"

//retrieves first TrackID
void CFileHandle::mGetFirstFile(std::string input) {

	hFind = FindFirstFileA((LPCSTR)(input + "\\test\\*").c_str(), &FileAttributes); //handle keeps index

	while ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '.')) {
		FindNextFileA(hFind, &FileAttributes);
	}
	TrackID.push_back(FileAttributes.cFileName); //writes Path into a Array
}

//retrieves Rest of TrackIDs
void CFileHandle::mGetNextFiles() {
	while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {

		FindNextFileA(hFind, &FileAttributes);

		if ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '.')){
			TrackID.push_back(FileAttributes.cFileName); //writes Path into a Array
		}
	}
	FindClose(hFind);
}


//Starts all that shit
void CFileHandle::Init(std::string classstring) {
	mGetFirstFile(classstring);
	mGetNextFiles();
}
