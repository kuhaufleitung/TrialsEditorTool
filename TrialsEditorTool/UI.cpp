#include "UI.h"


void CUI::mInitUI(HWND hWnd, HINSTANCE hInst) {
    
    Path.mPathDefaults();

    //check if first program start
    if (Path.isConfigFileCreated == false) {
        MessageBox(NULL, L"If you can't see any tracks, check your Path.cfg.\nIt has been created in the same folder.", L"First Start", MB_OK);

    }

    Path.mSetEditorPathVariable();
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
    
    Path.mSetEditorPathVariable();                      //Set Path to EditorTracks
    Path.mSetUbiPathVariable();

    Profile.mGetUbiID(Path.mUseUbiPath());              //ProfilePath
    Profile.mRearrangeID();                             //ProfileID for EditorFolder
    File->Init(Path.mUseEditorPath());                  //Retrieves Array of tracks -> trkfile here
    
    Port.mGetTemplatePath(Path.mUseEditorPath(), Profile.mGetProfileID());
    
    //creates Editor Folder
    Port.mCreateFolder(Path.mUseEditorPath(), Profile.mGetProfileID(), File->mGetTimeStamp(i));
    //copies necessary data to new Folder
    Port.mCopyNameMDA(Path.mUseEditorPath(), File->TrackID[i]);
    //copies modified Trackfile to new Folder
    Port.mModifyTrkfile(Path.mUseEditorPath(), File->TrackID[i]);

}

