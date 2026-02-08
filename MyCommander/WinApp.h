#pragma once
#include <windows.h>

class WinApp {
public:
    WinApp(HINSTANCE hInstance);
    int Run(int nCmdShow);
    HINSTANCE Instance() const { return _hInstance; }

private:
    void LoadStrings();
    bool RegisterMainWindow();
    bool CreateMainWindow(int nCmdShow);

private:
    HINSTANCE _hInstance;
    HWND _hMainWnd = nullptr;

    WCHAR _title[100] = L"";
    WCHAR _windowClass[100] = L"";
};