#pragma once
#include "MainWindow.h"
#include "DriveInfo.h"
using namespace System::IO;

LPCWSTR MainWindow::ClassName() const {
    return L"MainWindowClass";
}

BOOL MainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
    SetIcon(IDI_MYCOMMANDER);
    SetIconSmall(IDI_SMALL);
    SetMainMenu(IDC_MYCOMMANDER);

    auto drives = DriveInfo::GetDrives();
    // 
    // Tạo drive button giống total commander
    // Nạp danh sách các tập tin cùng với icon vào list view

    // Tạo ra layout container

    return true;
}

void MainWindow::OnPaint(HWND hwnd) {
    
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
