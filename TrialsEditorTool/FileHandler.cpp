#include "FileHandler.h"
#include "PathHandler.h"

//defines dialogbox directory
void CFileHandle::SetDirectory(CPathHandle* input) {
	SetCurrentDirectoryW(L"C:\\Test\\");
	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);
}


void CFileHandle::GetFirstFile(CPathHandle temp) {
	hmFind = FindFirstFileA("*", &FileAttributes);
	//std::cout << *FileAttributes.cFileName;
}


void CFileHandle::Init() {
	Path = new CPathHandle;
	Path->mPathDefaults();
	SetDirectory(Path); //passes Path Class
	//GetFirstFile(temp);
	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);
}
