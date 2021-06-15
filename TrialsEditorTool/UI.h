#pragma once
#include <fstream>
#include <string>
#include <Windows.h>
#include "PathHandler.h"
#include "TrackArray.h"
#include "PortTrack.h"
#include "Resource.h"
#include <CommCtrl.h>

enum GameSel {
	None = 0, Evo, Fusion, Rising
};


class CUI {
public:

	void mInitUI(HWND hWnd, HINSTANCE hInst);
	void mSetUI(HWND hWnd, HINSTANCE hInst);
	void mOnPortClick(int TrackIndex);
	void mOnRefreshClick();
	void mSetGame(int GameIndex);
	GameSel mGetGame();
	
private:

	CPathHandle Path;
	CTrackArray* File = new CTrackArray;
	CPort Port;

	GameSel Game;

	HWND hList = nullptr;
	HWND GameText = nullptr;
	HWND hGameSelection = nullptr;
	HWND hPortButton = nullptr;
	HWND hRefreshButton = nullptr;

};

