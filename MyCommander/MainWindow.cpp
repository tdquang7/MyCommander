#pragma once
#include "MainWindow.h"

LPCWSTR MainWindow::ClassName() const {
    return L"MainWindowClass";
}

BOOL MainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
    SetIcon(IDI_MYCOMMANDER);
    SetIconSmall(IDI_SMALL);
    SetMainMenu(IDC_MYCOMMANDER);

    return true;
}

void MainWindow::OnPaint(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(_hwnd, &ps);
    TextOutW(hdc, 20, 20, L"Hello Win32 OO", 15);
    EndPaint(_hwnd, &ps);
}

// Helper macro to simplify command handling 
#define COMMAND(target, handler) \
    if (id == target) return handler();

void MainWindow::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
    COMMAND(IDM_ABOUT, OnHelpAbout);
    COMMAND(IDM_EXIT, OnFileExit);
}

void MainWindow::OnHelpAbout() {
    AboutDialog::Show();
}

void MainWindow::OnFileExit() {
    PostQuitMessage(0);
}
