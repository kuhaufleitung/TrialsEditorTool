#include "UI.h"


void CUI::mInitUI(HWND hWnd, HINSTANCE hInst) {
   
    Path.mPathDefaults();

    CurrentGame = Selection::Game::None;

    if (!Path.isConfigFileCreated) {
        MessageBox(NULL, L"If you can't see any tracks, check your Path.cfg.\nIt has been created in the same folder.", L"First Start", MB_OK);

    }

    Path.mRetrieveEditorPathVariables();
    Path.mSetEditorPath(CurrentGame);
    Path.mSetUbiID(CurrentGame);

    mSetUI(hWnd, hInst);
}



void CUI::mSetUI(HWND hWnd, HINSTANCE hInst) {

    HFONT myFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);                 //get default Tahoma font
    HICON hIcon = LoadIconW(hInst, MAKEINTRESOURCEW(IDI_REFRESHICON));

    hGameSelection = CreateWindowW(WC_COMBOBOX, L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 20, 20, 400, 20, hWnd, (HMENU)IDC_DROPDOWN, 0, 0);
    hList = CreateWindowExW(WS_EX_CLIENTEDGE, L"listbox", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 20, 60, 400, 600, hWnd, (HMENU)IDC_LISTBOX, 0, 0);
    hPortButton = CreateWindowExW(WS_EX_WINDOWEDGE, L"Button", L"Port to Editor", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 665, 350, 40, hWnd, (HMENU)ID_PORTBUTTON, hInst, 0);
    hRefreshButton = CreateWindowExW(0, L"Button", L"", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_ICON | BS_DEFPUSHBUTTON, 380, 665, 40, 40, hWnd, (HMENU)ID_REFRESHBUTTON, hInst, 0);

    ComboBox_SetCueBannerText(hGameSelection, L"Select Game...");
    SendMessageW(hGameSelection, CB_ADDSTRING, 0, (LPARAM)TEXT("Trials Evolution Gold Edition"));
    SendMessageW(hGameSelection, CB_ADDSTRING, 0, (LPARAM)TEXT("Trials Fusion"));
    
    //disabled until tracknames parsing on rising is done
    //SendMessageW(hGameSelection, CB_ADDSTRING, 0, (LPARAM)TEXT("Trials Rising"));

    //set default Font & Icon
    SendMessageW(hGameSelection, WM_SETFONT, WPARAM(myFont), TRUE);
    SendMessageW(hList, WM_SETFONT, WPARAM(myFont), TRUE);
    SendMessageW(hPortButton, WM_SETFONT, WPARAM(myFont), TRUE);

    SendMessageW(hRefreshButton, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);

}



void CUI::mOnPortClick(int Trackindex) {
    
    if (Trackindex == -1) {
        MessageBox(NULL, L"No track was selected!", L"Error!", MB_OK | MB_ICONERROR);
        return;
    }
    

    switch (CurrentGame) {
    case Selection::Game::Evo:
    case Selection::Game::Fusion:
        {
            Port.mSetTemplatePath(Path.mGetEditorPath(), Path.mGetUbiID());
            Port.mCreateFolder(Path.mGetEditorPath(), Path.mGetUbiID(), File->mGetTimeStamp(Trackindex, CurrentGame));
            Port.mCopyNameMDA(Path.mGetEditorPath(), File->TrackAttributes[Trackindex].TrackID);
            Port.mModifyTrkfile(Path.mGetEditorPath(), File->TrackAttributes[Trackindex].TrackID, CurrentGame);

            MessageBox(NULL, L"Done", L"Porting Process", MB_OK);

        }break;
        case Selection::Game::Rising:
        {

        }break;
        case Selection::Game::None:
        {

        }break;
    }
        
}


void CUI::mOnRefreshClick() {

    File->TrackAttributes.clear();
    SendMessageW(hList, LB_RESETCONTENT, 0, 0);

    File->mSetTrackVector(Path.mGetEditorPath(), CurrentGame);
    File->mSortTracklist();
    
    for (int i = 0; i < File->TrackAttributes.size(); i++) {
        SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)File->TrackAttributes[i].TrackName.c_str());
    }
    
}

void CUI::mSetGame(int GameIndex, HWND hWnd) {
    
    //+1 because index doesnt know enum starts with none = 0
    GameIndex++;
    CurrentGame = (Selection::Game)GameIndex;

    Path.mSetEditorPath(CurrentGame);
    Path.mSetUbiID(CurrentGame);

    if (!Path.foundTrack) {
        MessageBox(NULL, L"No own created track was found!\nPlease create a track in the editor and restart the program. ", L"Error!", MB_OK | MB_ICONERROR);
        PostMessage(hWnd, WM_CLOSE, 0, 0);
        return;
    }

    //reset foundTrack in case user is switching multiple times
    Path.foundTrack = false;

    mOnRefreshClick();
}

Selection::Game CUI::mGetGame() {
    return CurrentGame;
}