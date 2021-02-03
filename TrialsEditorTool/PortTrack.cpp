#include "PortTrack.h"

//gets path of one own created track
std::string CPort::mGetTemplatePath(std::string input, std::string ProfileID) {

	hFindTemplate = FindFirstFileA((LPCSTR)(input + "\\*").c_str(), &data);
	TemplateFolder = data.cFileName;

	while (TemplateFolder.find(ProfileID) == std::string::npos) {
		FindNextFileA(hFindTemplate, &data);
		TemplateFolder = data.cFileName;
	}
	FindClose(hFindTemplate);
	return TemplateFolder;
}



std::string CPort::mUseTemplatePath() {
	return TemplateFolder;
}



//UbiID UNIXTIMESTAMP -0-0000000000000 (no spaces)
void CPort::mCreateFolder(std::string EditorPath, std::string ProfileID, std::string Unix) {


	NewTrackFolder = EditorPath + "\\" + ProfileID + Unix + "-0-0000000000000"; //for copying process

	CreateDirectoryA((LPCSTR) NewTrackFolder.c_str(), sec);
}



//copies requiered displayname file and metadata.mda to the created folder
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
void CPort::mModifyTrkfile(std::string EditorPath, std::string ExistingTrackID) {
	
	TemplateTrack.open(EditorPath + "\\" + TemplateFolder + "\\track.trk", std::fstream::binary);
	OriginalTrack.open(EditorPath + "\\" + ExistingTrackID + "\\track.trk", std::fstream::binary);
	NewTrack.open(NewTrackFolder + "\\track.trk", std::fstream::binary);



	//spaces will be ignored from reading
	TemplateTrack.unsetf(std::fstream::skipws);
	OriginalTrack.unsetf(std::fstream::skipws);
	
	//fill vectors with TrackData in Binary
	std::vector<unsigned char> bufferT(std::istreambuf_iterator<char>(TemplateTrack), {});
	std::vector<unsigned char> bufferO(std::istreambuf_iterator<char>(OriginalTrack), {});
	
	//Template track only needs content until 4C 5A 4D 41 5D -> pos = 59
	NewTrack.write((char*)&bufferT[0], 58);

	//Existing track only needs content after 4C 5A 4D 41 5D -> pos = 59
	NewTrack.seekp(58);	//set cursor pos
	NewTrack.write((char*)&bufferO[58], bufferO.size() - 58);



	TemplateTrack.close();
	OriginalTrack.close();
	NewTrack.close();
	
}
