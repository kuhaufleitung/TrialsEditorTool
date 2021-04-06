#include "TrackArray.h"

void CTrackArray::mSetTrackVector(std::string input) {

	hFind = FindFirstFileA((LPCSTR)(input + "\\*").c_str(), &FileAttributes);

	//filter out '.' and '..' directories
	while ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY
			|| (*FileAttributes.cFileName == '.')
			|| (*FileAttributes.cFileName == '..'))
	{
		FindNextFileA(hFind, &FileAttributes);
	}
	
	
	
	std::wstring Namebuffer;
	std::string OwnTrackFilter = "-0-0000000000000";

	while ((GetLastError() & ERROR_NO_MORE_FILES) == 0) {

		FindNextFileA(hFind, &FileAttributes);

		std::string duplicate = FileAttributes.cFileName;

		if ((FileAttributes.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || (*FileAttributes.cFileName == '..')) {

			if (duplicate.find(OwnTrackFilter) == std::string::npos) {

				Namebuffer = L"";

				NameOpen.open(input + "\\" + FileAttributes.cFileName + "\\" + "displayname");
				std::getline(NameOpen, Namebuffer);
				NameOpen.close();

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



bool CTrackArray::compareAlphabet(const TrackStruct& first, const TrackStruct& second) {
	
	return first.TrackName < second.TrackName;
}



void CTrackArray::mSortTracklist() {
	
	sort(TrackAttributes.begin(), TrackAttributes.end(), compareAlphabet);
}



void CTrackArray::Init(std::string Path) {
	mSetTrackVector(Path);
	mSortTracklist();
}

