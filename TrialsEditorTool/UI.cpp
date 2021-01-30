#include "UI.h"


void CUI::mInitUI(HWND hWnd, HINSTANCE hInst) {
    
    Path.mPathDefaults();
    Path.mSetEditorPath();
    File->Init(Path.mUseEditorPath().c_str());
    File->mGetTracknameList(Path.mUseEditorPath());
    mSetUI(hWnd, hInst);
}



void CUI::mSetUI(HWND hWnd, HINSTANCE hInst) {
    
    //creates Listbox
    hList = CreateWindowExW(WS_EX_CLIENTEDGE, L"listbox", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 20, 20, 400, 600, hWnd, (HMENU)IDC_LISTBOX, 0, 0);
    
    //fills Listbox with Track entries
    for (int i = 0; i < File->TrackNames.size(); i++) {
        SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)File->TrackNames[i].c_str());
    }
    //creates Button
    hButton = CreateWindowExW(WS_EX_WINDOWEDGE, L"button", L"Port to Editor", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 630, 400, 40, hWnd, (HMENU)ID_PORTBUTTON, hInst, 0);

}



void CUI::mOnButtonClick(int i) {
    
    Profile.mGetUbiID(Path.mGetUbiPath());              //ProfilePath
    Profile.mRearrangeID();                             //ProfileID for EditorFolder
    Path.mSetEditorPath();                              //Set Path to EditorTracks
    File->Init(Path.mUseEditorPath());                  //Retrieves Array of tracks -> trkfile here
    
    Port.mGetTemplatePath(Path.mUseEditorPath(), Profile.mGetProfileID());
    
    //create Editor Folder
    Port.mCreateFolder(Path.mUseEditorPath(), Profile.mGetProfileID(), File->mGetTimeStamp(i));
    Port.mCopyNameMDA(Path.mUseEditorPath(), File->TrackID[i]);


}

