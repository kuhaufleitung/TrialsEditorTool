#include "UI.h"


void CUI::mInitUI(HWND hWnd, HINSTANCE hInst) {
    
    Path.mPathDefaults();

    if (Path.isConfigFileCreated == false) {
        MessageBox(NULL, L"If you can't see any tracks, check your Path.cfg.\nIt has been created in the same folder.", L"First Start", MB_OK);

    }

    Path.mSetEditorPathVariable();
    Path.mSetUbiID();

    if (Path.foundTrack == false) {
        MessageBox(NULL, L"No own created track was found!\nPlease create a track in the editor and restart the program. ", L"Error!", MB_OK | MB_ICONERROR);
        PostMessage(hWnd, WM_CLOSE, 0, 0);
        return;
    }


    File->Init(Path.mGetEditorPath());
    mSetUI(hWnd, hInst);
}



void CUI::mSetUI(HWND hWnd, HINSTANCE hInst) {

    HFONT myFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);                 //get default Tahoma font
    HICON hIcon = LoadIconW(hInst, MAKEINTRESOURCEW(IDI_REFRESHICON));

    hList = CreateWindowExW(WS_EX_CLIENTEDGE, L"listbox", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 20, 20, 400, 600, hWnd, (HMENU)IDC_LISTBOX, 0, 0);
    
    //fills Listbox with Track entries
    for (int i = 0; i < File->TrackAttributes.size(); i++) {
        SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)File->TrackAttributes[i].TrackName.c_str());
    }

    hPortButton = CreateWindowExW(WS_EX_WINDOWEDGE, L"Button", L"Port to Editor", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 630, 350, 40, hWnd, (HMENU)ID_PORTBUTTON, hInst, 0);
    hRefreshButton = CreateWindowExW(0, L"Button", L"", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_ICON, 380, 630, 40, 40, hWnd, (HMENU)ID_REFRESHBUTTON, hInst, 0);
    

    //set default Font & Icon
    SendMessage(hList, WM_SETFONT, WPARAM(myFont), TRUE);
    SendMessage(hPortButton, WM_SETFONT, WPARAM(myFont), TRUE);
    SendMessageW(hRefreshButton, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);
}



void CUI::mOnPortClick(int i) {
    
    if (i == -1) {
        MessageBox(NULL, L"No track was selected!", L"Error!", MB_OK | MB_ICONERROR);
        return;
    }
    
    Port.mSetTemplatePath(Path.mGetEditorPath(), Path.mGetUbiID());
    
    Port.mCreateFolder(Path.mGetEditorPath(), Path.mGetUbiID(), File->mGetTimeStamp(i));
    Port.mCopyNameMDA(Path.mGetEditorPath(), File->TrackAttributes[i].TrackID);
    Port.mModifyTrkfile(Path.mGetEditorPath(), File->TrackAttributes[i].TrackID);

    MessageBox(NULL, L"Done", L"Porting Process", MB_OK);

}

void CUI::mOnRefreshClick() {

    File->TrackAttributes.clear();
    SendMessageW(hList, LB_RESETCONTENT, 0, 0);

    File->mSetTrackVector(Path.mGetEditorPath());
    File->mSortTracklist();
    
    for (int i = 0; i < File->TrackAttributes.size(); i++) {
        SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)File->TrackAttributes[i].TrackName.c_str());
    }
    
}