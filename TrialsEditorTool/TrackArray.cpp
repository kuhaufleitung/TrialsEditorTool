#include "TrackArray.h"

//retrieves first TrackID
void CTrackArray::mSetTrackVector(std::string input) {

	hFind = FindFirstFileA((LPCSTR)(input + "\\*").c_str(), &FileAttributes); //handle keeps index

	//filter out '.' and '..' directories
	while ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY
			|| (*FileAttributes.cFileName == '.')
			|| (*FileAttributes.cFileName == '..'))
	{
		FindNextFileA(hFind, &FileAttributes);
	}
	
	
	
//get rest of tracks
	std::wstring Namebuffer;
	std::string OwnTrackFilter = "-0-0000000000000";

	while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {

		FindNextFileA(hFind, &FileAttributes);

		//check for duplicate FileNames
		std::string duplicate = FileAttributes.cFileName;

		if ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '..')) {

			if (duplicate.find(OwnTrackFilter) == std::string::npos) {

				Namebuffer = L"";

				//get the Trackname from that ID
				NameOpen.open(input + "\\" + FileAttributes.cFileName + "\\" + "displayname");
				std::getline(NameOpen, Namebuffer);
				NameOpen.close();

				//writes both Name and Path into an array
				TrackAttributes.push_back({ Namebuffer, FileAttributes.cFileName });
			}
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
	mSetTrackVector(classstring);
	mSortTracklist();
}

