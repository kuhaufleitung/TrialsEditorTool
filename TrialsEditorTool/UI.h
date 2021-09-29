#pragma once
#include <fstream>
#include <string>
#include <Windows.h>
#include "PathHandler.h"
#include "TrackArray.h"
#include "PortTrack.h"
#include "Resource.h"
#include <CommCtrl.h>
#include "enum.h"

class CUI {
public:

	void mInitUI(HWND hWnd, HINSTANCE hInst);
	void mSetUI(HWND hWnd, HINSTANCE hInst);
	void mOnPortClick(int TrackIndex);
	void mOnRefreshClick();
	void mSetGame(int GameIndex, HWND hWnd);
	Selection::Game mGetGame();
	
private:

	CPathHandle Path;
	CTrackArray* File = new CTrackArray;
	CPort Port;

	Selection::Game CurrentGame = Selection::Game::None;

	HWND hList = nullptr;
	HWND hGameSelection = nullptr;
	HWND hPortButton = nullptr;
	HWND hRefreshButton = nullptr;

};

