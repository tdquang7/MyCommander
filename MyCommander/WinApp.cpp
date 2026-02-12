// WinApp.cpp
#include "WinApp.h"
#include "resource.h"
#include "MainWindow.h"

WinApp& WinApp::Current() { 
    static WinApp _instance;
    return _instance;
}

WinApp::WinApp():_hInstance(GetModuleHandleW(nullptr)) {};

HINSTANCE WinApp::Instance() const { return _hInstance; }
HWND WinApp::MainWindowHandle() const { return _hMainWnd; }
HWND WinApp::ActiveWindowHandle() const { return _hActiveWnd; }

int WinApp::Run(int nCmdShow) {
    MainWindow win;
    if (!win.Create(L"Tiêu đề", WS_OVERLAPPEDWINDOW))
        return 0;

    win.Show(nCmdShow);

    HACCEL hAccel = LoadAccelerators(_hInstance, MAKEINTRESOURCE(IDC_MYCOMMANDER));

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}
