#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Resource.h"


class CTrackArray {
public:

	void Init(std::string classstring);
	void mGetFirstTrack(std::string input);
	void mGetNextTracks(std::string input);

	std::string mGetTimeStamp(int i);
	//bool mNameFileFound(const char* filename);


	struct TrackStruct {
		std::wstring TrackName;
		std::string TrackID;
	};

	std::vector<TrackStruct> TrackAttributes;

private:

	std::wifstream NameOpen;

	HANDLE hFind;
	WIN32_FIND_DATAA FileAttributes;
};