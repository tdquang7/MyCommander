#pragma once
#include <windows.h>
#include "AboutDialog.h"
#include "resource.h"
#include "WinApp.h"

class AboutDialog {
public:
    static void Show();

private:
    static INT_PTR CALLBACK DialogProc(
        HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
};