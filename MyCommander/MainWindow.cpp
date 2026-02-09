#pragma once
#include "MainWindow.h"

LPCWSTR MainWindow::ClassName() const {
    return L"MainWindowClass";
}

void MainWindow::OnCreate() {
    SetIcon(IDI_MYCOMMANDER);
    SetIconSmall(IDI_SMALL);
    SetMainMenu(IDC_MYCOMMANDER);
}

void MainWindow::OnPaint() {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(_hwnd, &ps);
    TextOutW(hdc, 20, 20, L"Hello Win32 OO", 15);
    EndPaint(_hwnd, &ps);
}

void MainWindow::OnCommand(WPARAM wParam, LPARAM lParam) {
    COMMAND(IDM_ABOUT, OnHelpAbout);
    COMMAND(IDM_EXIT, OnFileExit);
}

void MainWindow::OnHelpAbout(WPARAM wParam, LPARAM lParam) {
    AboutDialog::Show();
}

void MainWindow::OnFileExit(WPARAM wParam, LPARAM lParam) {
    PostQuitMessage(0);
}
