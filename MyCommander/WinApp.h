#pragma once
#include <windows.h>
#include <memory>
#include "Debug.h"

class WinApp {
public:
    static WinApp& Current();
    HINSTANCE Instance() const;
    HWND MainWindowHandle() const;
    HWND ActiveWindowHandle() const;
    WinApp(const WinApp&) = delete;
    int Run(int nCmdShow);
    ~WinApp() = default;
private:
    WinApp();
private:
	HINSTANCE _hInstance = nullptr;
    HWND _hMainWnd = nullptr;
	HWND _hActiveWnd = nullptr;
};