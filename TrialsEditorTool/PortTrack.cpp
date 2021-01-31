#include "PortTrack.h"


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
void CPort::mCopyNameMDAtrk(std::string EditorPath, std::string ExistingTrackID) {
	
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
	
	//Copy TemplateTrack
	failM = CopyFileA((LPCSTR)(ExistingTemplatePath + "\\track.trk").c_str(), (LPCSTR)(NewTrackFolder + "\\track.trk").c_str(), 0);
	if (!failM) {
		DWORD error = GetLastError();
	}
}

//copies original track to destination and replaces first few bytes from TemplateTrack
//search for:    4C 5A 4D 41 5D 00 00 02 00
void CPort::mModifyTrkfile(std::string EditorPath, std::string ExistingTrackID) {
	
	OriginalTrack.open(EditorPath + "\\" + ExistingTrackID + "\\track.trk", std::fstream::binary);
	NewTrack.open(NewTrackFolder + "\\track.trk", std::fstream::binary || std::fstream::app);

	//spaces will be ignored from reading
	OriginalTrack.unsetf(std::fstream::skipws);

	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(OriginalTrack), {});
	
	NewTrack.seekp(60);
	NewTrack.write((char*)&buffer[60], buffer.size());

	OriginalTrack.close();
	NewTrack.close();
	
}
