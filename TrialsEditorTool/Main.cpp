#include <iostream>
#include "PathHandler.h"
#include "FileHandler.h"
#include "DialogBox.h"


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpcmdline, int ncmdshow)

{
	WNDCLASSEX windowclass;
	HWND hWnd;
	MSG message;

	const TCHAR szClassName[] = TEXT("Erstes Fenster");

	windowclass.cbSize = sizeof(WNDCLASSEX);

	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	windowclass.lpfnWndProc = WindowProc;

	windowclass.cbClsExtra = 0;
	windowclass.cbWndExtra = 0;

	windowclass.hInstance = hInst;

	windowclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	windowclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	windowclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;

	windowclass.lpszMenuName = NULL;

	windowclass.lpszClassName = szClassName;

	if (!RegisterClassEx(&windowclass))
		return 0;

	hWnd = CreateWindowEx(NULL, szClassName, TEXT("Das erste Fenster!"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 300, 250, NULL, NULL, hInst, NULL);

	if (hWnd == NULL)
		return 0;

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
		return (int)(message.wParam);

		CDialogBox Box;
		Box.Init();

		//std::wcout << Box.GetDirectory();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return (0);
	}

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			PostQuitMessage(0);
			return (0);
		}
		}
	} break;

	}

	return (DefWindowProc(hWnd, message, wParam, lParam));
}