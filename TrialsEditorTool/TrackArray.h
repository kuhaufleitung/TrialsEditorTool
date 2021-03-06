#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

class CTrackArray {
public:

	void Init(std::string classstring);
	void mGetFirstTrack(std::string input);
	void mGetNextTracks(std::string input);
	void mSortTracklist();

	std::string mGetTimeStamp(int i);


	struct TrackStruct {
		std::wstring TrackName;
		std::string TrackID;
	};

	std::vector<TrackStruct> TrackAttributes;
	static bool compareAlphabet(const TrackStruct& first, const TrackStruct& second);

private:

	std::wifstream NameOpen;

	HANDLE hFind;
	WIN32_FIND_DATAA FileAttributes;
};