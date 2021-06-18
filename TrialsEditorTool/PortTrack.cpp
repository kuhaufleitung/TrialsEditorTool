#include "PortTrack.h"


//gets path of one own created track
std::string CPort::mSetTemplatePath(std::string input, std::string ProfileID) {

	hFindTemplate = FindFirstFileA((LPCSTR)(input + "\\*").c_str(), &data);
	TemplateFolder = data.cFileName;

	while (TemplateFolder.find(ProfileID) == std::string::npos) {
		FindNextFileA(hFindTemplate, &data);
		TemplateFolder = data.cFileName;
	}
	FindClose(hFindTemplate);
	return TemplateFolder;
}



std::string CPort::mGetTemplatePath() {
	return TemplateFolder;
}



//UbiID UNIXTIMESTAMP -0-0000000000000 (no spaces)
void CPort::mCreateFolder(std::string EditorPath, std::string ProfileID, std::string Unix) {


	NewTrackFolder = EditorPath + "\\" + ProfileID + Unix + "-0-0000000000000"; //for copying process

	CreateDirectoryA((LPCSTR) NewTrackFolder.c_str(), sec);
}



void CPort::mCopyNameMDA(std::string EditorPath, std::string ExistingTrackID) {
	
	//Copy displayname
	std::string ExistingTrackPath = EditorPath + "\\" + ExistingTrackID;
	
	BOOL failD = CopyFileA((LPCSTR)(ExistingTrackPath + "\\displayname").c_str(), (LPCSTR)(NewTrackFolder + "\\displayname").c_str(), 0);
	if (!failD) {
		DWORD error = GetLastError();
	}



	
	//Copy metadata.mda
	std::string ExistingTemplatePath = EditorPath + "\\" + TemplateFolder;

	BOOL failM = CopyFileA((LPCSTR)(ExistingTemplatePath + "\\metadata.mda").c_str(), (LPCSTR)(NewTrackFolder + "\\metadata.mda").c_str(), 0);
	if (!failM) {
		DWORD error = GetLastError();
	}
	
}



//copies original track to destination and replaces first few bytes from TemplateTrack
void CPort::mModifyTrkfile(std::string EditorPath, std::string ExistingTrackID, Selection::Game Game) {
	
	TemplateTrack.open(EditorPath + "\\" + TemplateFolder + "\\track.trk", std::fstream::binary);
	OriginalTrack.open(EditorPath + "\\" + ExistingTrackID + "\\track.trk", std::fstream::binary);
	NewTrack.open(NewTrackFolder + "\\track.trk", std::fstream::binary);



	//spaces will be ignored from reading
	TemplateTrack.unsetf(std::fstream::skipws);
	OriginalTrack.unsetf(std::fstream::skipws);
	
	//fill vectors with TrackData in Binary
	std::vector<unsigned char> bufferT(std::istreambuf_iterator<char>(TemplateTrack), {});
	std::vector<unsigned char> bufferO(std::istreambuf_iterator<char>(OriginalTrack), {});
	
	switch (Game) {
	case Selection::Game::Evo:
	{
		//Template track only needs content until 0x25 -> pos = 38
		NewTrack.write((char*)&bufferT[0], 38);

		//Existing track only needs content after 0x25 -> pos = 38
		NewTrack.seekp(38);	//set cursor pos
		NewTrack.write((char*)&bufferO[38], bufferO.size() - 38);

	}break;
	case Selection::Game::Fusion:
	{
		//0x39 -> pos = 58
		NewTrack.write((char*)&bufferT[0], 58);

		//0x39 -> pos = 58
		NewTrack.seekp(58);
		NewTrack.write((char*)&bufferO[58], bufferO.size() - 58);

	}break;
	}


	TemplateTrack.close();
	OriginalTrack.close();
	NewTrack.close();
	
}
