// TrialsEditorTool.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Resource.h"
#include "PathHandler.h"
#include "TrackArray.h"
#include "ProfileID.h"
#include "CopyProcess.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWnd;
HWND hList;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    ListBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam, std::string ListArray);
  
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    ////////////////////////////////////////////////////////
    //actualProgrammCode
    
    CPathHandle Path;
    Path.mPathDefaults();
    
    TrackArray* File = new TrackArray;
    File->Init(Path.mGetEditorPath().c_str());
    
    CProfileID Profile;
    Profile.mGetProfileID(Path.mGetUbiPath());
    Profile.mRearrangeID();
    
    CCopy* Copy = new CCopy;
    Copy->mGetTemplatePath(Path.mGetEditorPath().c_str());

    File->mGetTracknameList(Path.mGetEditorPath());
    //
    ////////////////////////////////////////////////////////
    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TRIALSEDITORTOOL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRIALSEDITORTOOL));

    hList = CreateWindowExW(WS_EX_CLIENTEDGE, L"listbox", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 35, 50, 400, 600, hWnd, (HMENU)IDC_LISTBOX, 0, 0);
    for (int i = 0; i < File->TrackNames.size(); i++) {
        SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)File->TrackNames[i].c_str());
    }
    UpdateWindow(hWnd);


    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;

}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRIALSEDITORTOOL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TRIALSEDITORTOOL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
/*
INT_PTR CALLBACK ListBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam, std::string ListArray)
{
        
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Add items to list. 
        HWND hwndList = GetDlgItem(hDlg, IDC_LISTBOX);
        for (int i = 0; i < ListArray.size(); i++)
        {
            int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
                (LPARAM)ListArray[i]);
            // Set the array index of the player as item data.
            // This enables us to retrieve the item from the array
            // even after the items are sorted by the list box.
            SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
        }
        // Set input focus to the list box.
        SetFocus(hwndList);
        return TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;

        case IDC_LISTBOX:
        {
            switch (HIWORD(wParam))
            {
            case LBN_SELCHANGE:
            {
                HWND hwndList = GetDlgItem(hDlg, IDC_LISTBOX);

                // Get selected index.
                int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);

                // Get item data.
                int i = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);

                // Do something with the data from Roster[i]
                TCHAR buff[MAX_PATH];
                StringCbPrintf(buff, ARRAYSIZE(buff),
                    TEXT("Position: %s\nGames played: %d\nGoals: %d"),
                    Roster[i].achPosition, Roster[i].nGamesPlayed,
                    Roster[i].nGoalsScored);

                SetDlgItemText(hDlg, IDC_STATISTICS, buff);
                return TRUE; 
            }
            }
        }
        return TRUE;
        }
    }
    return FALSE;
}
*/