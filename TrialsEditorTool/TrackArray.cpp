#include "TrackArray.h"

void CTrackArray::mSetTrackVector(std::string input, Selection::Game Game) {

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

			switch (Game) {
			case Selection::Game::Evo:
			case Selection::Game::Fusion:
			{
				if (duplicate.find(OwnTrackFilter) == std::string::npos) {

					Namebuffer = L"";

					NameOpen.open(input + "\\" + FileAttributes.cFileName + "\\" + "displayname");
					std::getline(NameOpen, Namebuffer);
					NameOpen.close();

					TrackAttributes.push_back({ Namebuffer, FileAttributes.cFileName });
				}

			}break;
			case Selection::Game::Rising:
			{
				Namebuffer = L"";

				//TODO: Fetch DisplayName from mda file
				NameOpen.open(input + "\\" + FileAttributes.cFileName + "\\" + "displayname");
				std::getline(NameOpen, Namebuffer);
				NameOpen.close();

				TrackAttributes.push_back({ Namebuffer, FileAttributes.cFileName });

			}break;
			}
		}

	}
	FindClose(hFind);
}



//extracts the UnixTimeStamp from the TrackDirectory (hexadem)
std::string CTrackArray::mGetTimeStamp(int i, Selection::Game Game) {
	
	std::string UnixStamp = TrackAttributes[i].TrackID;

	switch (Game) {
		case Selection::Game::Evo:
		{
			UnixStamp.erase(0, 19);
			UnixStamp.erase(7, 16);
		}break;
		case Selection::Game::Fusion:
		{
			UnixStamp.erase(0, 32);
			UnixStamp.erase(10, 16);
		}break;
		case Selection::Game::Rising:
		{
			return UnixStamp = "";
		}break;
	}
	
	return UnixStamp;
}



bool CTrackArray::compareAlphabet(const TrackStruct& first, const TrackStruct& second) {
	
	return first.TrackName < second.TrackName;
}



void CTrackArray::mSortTracklist() {
	
	sort(TrackAttributes.begin(), TrackAttributes.end(), compareAlphabet);
}