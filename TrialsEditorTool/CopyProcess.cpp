#include "CopyProcess.h"

std::string CCopy::mGetTemplatePath(std::string input) {

	hFindTemp = FindFirstFileA((LPCSTR)(input + "//*").c_str(), &data);
	mTemplateFolder = data.cFileName;

	while (mTemplateFolder.find("0000000000000") == std::string::npos) {
		FindNextFileA(hFindTemp, &data);
		mTemplateFolder = data.cFileName;
	}
	FindClose(hFindTemp);
	return mTemplateFolder;
}

void CCopy::mUI(HWND hWnd, HINSTANCE hInst) {
    
    Path.mPathDefaults();

    File->Init(Path.mGetEditorPath().c_str());

    //Profile.mGetProfileID(Path.mGetUbiPath());
    //Profile.mRearrangeID();

    //mGetTemplatePath(Path.mGetEditorPath().c_str());

    File->mGetTracknameList(Path.mGetEditorPath());

    mSetUI(hWnd, hInst);
}



void CCopy::mSetUI(HWND hWnd, HINSTANCE hInst) {
    
    //creates Listbox
    hList = CreateWindowExW(WS_EX_CLIENTEDGE, L"listbox", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 20, 20, 400, 600, hWnd, (HMENU)IDC_LISTBOX, 0, 0);
    
    //fills Listbox with Track entries
    for (int i = 0; i < File->TrackNames.size(); i++) {
        SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)File->TrackNames[i].c_str());
    }
    //creates Button
    hButton = CreateWindowExW(WS_EX_WINDOWEDGE, L"button", L"Port to Editor", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 630, 400, 40, hWnd, (HMENU)ID_PORTBUTTON, hInst, 0);

}

