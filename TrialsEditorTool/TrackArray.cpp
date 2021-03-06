#include "TrackArray.h"

//retrieves first TrackID
void CTrackArray::mGetFirstTrack(std::string input) {

	hFind = FindFirstFileA((LPCSTR)(input + "\\*").c_str(), &FileAttributes); //handle keeps index

	while ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '.') || (*FileAttributes.cFileName == '..')) {
		FindNextFileA(hFind, &FileAttributes);
	}
	
	std::wstring buffer;

	//get the Trackname from that ID
	NameOpen.open(input + "\\" + FileAttributes.cFileName + "\\" + "displayname");
	std::getline(NameOpen, buffer);
	NameOpen.close();

	//writes both Name and Path into an array
	TrackAttributes.push_back({ buffer, FileAttributes.cFileName });
}



//retrieves Rest of TrackIDs
void CTrackArray::mGetNextTracks(std::string input) {
	
	std::wstring buffer;

	while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {

		FindNextFileA(hFind, &FileAttributes);

		if ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '.')){
			
			buffer = L"";

			//get the Trackname from that ID
			NameOpen.open(input + "\\" + FileAttributes.cFileName + "\\" + "displayname");
			std::getline(NameOpen, buffer);
			NameOpen.close();

			//writes both Name and Path into an array
			TrackAttributes.push_back({ buffer, FileAttributes.cFileName });
		}
	}
	FindClose(hFind);
}



//extracts the UnixTimeStamp from the TrackDirectory (hexadem)
std::string CTrackArray::mGetTimeStamp(int i) {
	std::string UnixStamp = TrackAttributes[i].TrackID;
	UnixStamp.erase(0, 32);
	UnixStamp.erase(10, 16);
	return UnixStamp;
}



//compares two names
bool CTrackArray::compareAlphabet(const TrackStruct& first, const TrackStruct& second) {
	
	return first.TrackName < second.TrackName;
}



//sort tracklist alphabetically
void CTrackArray::mSortTracklist() {
	
	sort(TrackAttributes.begin(), TrackAttributes.end(), compareAlphabet);
}



//Starts all that shit
void CTrackArray::Init(std::string classstring) {
	mGetFirstTrack(classstring);
	mGetNextTracks(classstring);
	mSortTracklist();
}

