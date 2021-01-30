#include "TrackArray.h"

//retrieves first TrackID
void CTrackArray::mGetFirstFile(std::string input) {

	hFind = FindFirstFileA((LPCSTR)(input + "\\*").c_str(), &FileAttributes); //handle keeps index

	while ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '.') || (*FileAttributes.cFileName == '..')) {
		FindNextFileA(hFind, &FileAttributes);
	}
	TrackID.push_back(FileAttributes.cFileName); //writes Path into a Array
}



//retrieves Rest of TrackIDs
void CTrackArray::mGetNextFiles() {
	while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {

		FindNextFileA(hFind, &FileAttributes);

		if ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '.')){
			TrackID.push_back(FileAttributes.cFileName); //writes Path into a Array
		}
	}
	FindClose(hFind);
}



void CTrackArray::mGetTracknameList(std::string Path) {
	for (int i = 0; i < TrackID.size(); i++) {
		
		NameOpen.open(Path + "\\" + TrackID[i] + "\\" + "displayname");
		std::getline(NameOpen, buffer);
		TrackNames.push_back(buffer);
		NameOpen.close();
	}
}
/*
//checks displayname access
bool CTrackArray::mNameFileFound(const char* filename)
{
	std::ifstream infile(filename);
	return infile.good();
}
*/



std::string CTrackArray::mGetTimeStamp(int i) {
	std::string UnixStamp = TrackID[i];
	UnixStamp.erase(0, 32);
	UnixStamp.erase(10, 16);
	return UnixStamp;
}



//Starts all that shit
void CTrackArray::Init(std::string classstring) {
	mGetFirstFile(classstring);
	mGetNextFiles();
}

