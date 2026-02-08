// WinApp.cpp
#include "WinApp.h"
#include "resource.h"
#include "MainWindow.h"

WinApp::WinApp(HINSTANCE instance)
    : _hInstance(instance) {
}

int WinApp::Run(int nCmdShow) {
    LoadStrings();
    if (!RegisterMainWindow()) return FALSE;
    if (!CreateMainWindow(nCmdShow)) return FALSE;

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

void WinApp::LoadStrings() {
    LoadStringW(_hInstance, IDS_APP_TITLE, _title, 100);
    LoadStringW(_hInstance, IDC_MYCOMMANDER, _windowClass, 100);
}

bool WinApp::RegisterMainWindow() {
    bool result = MainWindow::Register(_hInstance, _windowClass);
    if (!result && GetLastError() == ERROR_CLASS_ALREADY_EXISTS) {
        return true; // Class already registered, that's OK
    }
    return result;
}

bool WinApp::CreateMainWindow(int nCmdShow) {
    _hMainWnd = MainWindow::Create(
        _hInstance,
        _windowClass,
        _title
    );

    if (!_hMainWnd) {
        DWORD error = GetLastError();
        WCHAR errorMsg[256];
        wsprintf(errorMsg, L"Failed to create window. Error code: %d", error);
        MessageBox(nullptr, errorMsg, L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    ShowWindow(_hMainWnd, nCmdShow);
    UpdateWindow(_hMainWnd);
    return true;
}