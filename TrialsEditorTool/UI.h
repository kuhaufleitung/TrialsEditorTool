#pragma once
#include <fstream>
#include <string>
#include <Windows.h>
#include "PathHandler.h"
#include "TrackArray.h"
#include "PortTrack.h"
#include "Resource.h"

class CUI {
public:

	void mInitUI(HWND hWnd, HINSTANCE hInst);
	void mSetUI(HWND hWnd, HINSTANCE hInst);
	void mOnButtonClick(int i);
	


private:

	CPathHandle Path;
	CTrackArray* File = new CTrackArray;
	CPort Port;

	HWND hList;
	HWND hButton;

};