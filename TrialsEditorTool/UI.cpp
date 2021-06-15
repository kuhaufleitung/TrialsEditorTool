#include "UI.h"


void CUI::mInitUI(HWND hWnd, HINSTANCE hInst) {
   
    Path.mPathDefaults();

    Game = Game::GameSel::None;

    if (Path.isConfigFileCreated == false) {
        MessageBox(NULL, L"If you can't see any tracks, check your Path.cfg.\nIt has been created in the same folder.", L"First Start", MB_OK);

    }

    Path.mRetrieveEditorPathVariables();
    Path.mSetEditorPath(Game);
    Path.mSetUbiID(Game);

    mSetUI(hWnd, hInst);
}



void CUI::mSetUI(HWND hWnd, HINSTANCE hInst) {

    HFONT myFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);                 //get default Tahoma font
    HICON hIcon = LoadIconW(hInst, MAKEINTRESOURCEW(IDI_REFRESHICON));

    GameText = CreateWindowW(TEXT("Static"), TEXT("Game:"), WS_CHILD | WS_VISIBLE | WS_EX_TRANSPARENT, 20, 10, 32, 15, hWnd, (HMENU)IDC_STATICGAMELABEL, NULL, NULL);
    hGameSelection = CreateWindowW(WC_COMBOBOX, L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 20, 40, 400, 20, hWnd, (HMENU)IDC_DROPDOWN, 0, 0);
    hList = CreateWindowExW(WS_EX_CLIENTEDGE, L"listbox", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 20, 80, 400, 600, hWnd, (HMENU)IDC_LISTBOX, 0, 0);
    hPortButton = CreateWindowExW(WS_EX_WINDOWEDGE, L"Button", L"Port to Editor", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 690, 350, 40, hWnd, (HMENU)ID_PORTBUTTON, hInst, 0);
    hRefreshButton = CreateWindowExW(0, L"Button", L"", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_ICON | BS_DEFPUSHBUTTON, 380, 690, 40, 40, hWnd, (HMENU)ID_REFRESHBUTTON, hInst, 0);


    SendMessageW(hGameSelection, CB_ADDSTRING, 0, (LPARAM)TEXT("Trials Evolution Gold Edition"));
    SendMessageW(hGameSelection, CB_ADDSTRING, 0, (LPARAM)TEXT("Trials Fusion"));
    SendMessageW(hGameSelection, CB_ADDSTRING, 0, (LPARAM)TEXT("Trials Rising"));
    

    //set default Font & Icon
    SendMessage(GameText, WM_SETFONT, WPARAM(myFont), TRUE);
    SendMessage(hGameSelection, WM_SETFONT, WPARAM(myFont), TRUE);
    SendMessage(hList, WM_SETFONT, WPARAM(myFont), TRUE);
    SendMessage(hPortButton, WM_SETFONT, WPARAM(myFont), TRUE);

    SendMessageW(hRefreshButton, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);

}



void CUI::mOnPortClick(int Trackindex) {
    
    if (Trackindex == -1) {
        MessageBox(NULL, L"No track was selected!", L"Error!", MB_OK | MB_ICONERROR);
        return;
    }
    

    switch (Game){
    case Game::GameSel::Evo:
        {

        }break;
        case Game::GameSel::Fusion:
        {

        }break;
        case Game::GameSel::Rising:
        {

        }break;
        case Game::GameSel::None:
        {

        }break;
    }
        

    Port.mSetTemplatePath(Path.mGetEditorPath(), Path.mGetUbiID());
    
    Port.mCreateFolder(Path.mGetEditorPath(), Path.mGetUbiID(), File->mGetTimeStamp(Trackindex));
    Port.mCopyNameMDA(Path.mGetEditorPath(), File->TrackAttributes[Trackindex].TrackID);
    Port.mModifyTrkfile(Path.mGetEditorPath(), File->TrackAttributes[Trackindex].TrackID);

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

void CUI::mSetGame(int GameIndex, HWND hWnd) {
    
    //+1 because index doesnt know enum starts with none = 0
    GameIndex++;
    Game = (Game::GameSel)GameIndex;

    Path.mSetEditorPath(Game);
    Path.mSetUbiID(Game);

    if (Path.foundTrack == false) {
        MessageBox(NULL, L"No own created track was found!\nPlease create a track in the editor and restart the program. ", L"Error!", MB_OK | MB_ICONERROR);
        PostMessage(hWnd, WM_CLOSE, 0, 0);
        return;
    }

    mOnRefreshClick();
}

Game::GameSel CUI::mGetGame() {
    return Game;
}