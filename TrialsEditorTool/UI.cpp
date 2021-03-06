#include "UI.h"


void CUI::mInitUI(HWND hWnd, HINSTANCE hInst) {
    
    Path.mPathDefaults();

    //check if first program start
    if (Path.isConfigFileCreated == false) {
        MessageBox(NULL, L"If you can't see any tracks, check your Path.cfg.\nIt has been created in the same folder.", L"First Start", MB_OK);

    }

    Path.mSetEditorPathVariable();                      //Set Path to EditorTracks
    Path.mSetUbiID();                                   //ProfileID
    File->Init(Path.mGetEditorPath());
    mSetUI(hWnd, hInst);
}



void CUI::mSetUI(HWND hWnd, HINSTANCE hInst) {

    HFONT myFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT); //get default Tahoma font


    //creates Listbox
    hList = CreateWindowExW(WS_EX_CLIENTEDGE, L"listbox", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 20, 20, 400, 600, hWnd, (HMENU)IDC_LISTBOX, 0, 0);
    
    //fills Listbox with Track entries
    for (int i = 0; i < File->TrackAttributes.size(); i++) {
        SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)File->TrackAttributes[i].TrackName.c_str());
    }
    //creates Button
    hButton = CreateWindowExW(WS_EX_WINDOWEDGE, L"button", L"Port to Editor", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 630, 400, 40, hWnd, (HMENU)ID_PORTBUTTON, hInst, 0);

    //set default Font
    SendMessage(hList, WM_SETFONT, WPARAM(myFont), TRUE);
    SendMessage(hButton, WM_SETFONT, WPARAM(myFont), TRUE);

}



void CUI::mOnButtonClick(int i) {
    
    if (i == -1) {
        MessageBox(NULL, L"No track was selected!", L"Error!", MB_OK | MB_ICONERROR);
        return;
    }
    
    Port.mSetTemplatePath(Path.mGetEditorPath(), Path.mGetUbiID());
    
    //creates Editor Folder
    Port.mCreateFolder(Path.mGetEditorPath(), Path.mGetUbiID(), File->mGetTimeStamp(i));
    //copies necessary data to new Folder
    Port.mCopyNameMDA(Path.mGetEditorPath(), File->TrackAttributes[i].TrackID);
    //copies modified Trackfile to new Folder
    Port.mModifyTrkfile(Path.mGetEditorPath(), File->TrackAttributes[i].TrackID);

    MessageBox(NULL, L"Done", L"Porting Process", MB_OK);

}

