#pragma once
#include <windows.h>

class AboutDialog {
public:
    static void Show(HINSTANCE hInstance);

private:
    static INT_PTR CALLBACK DialogProc(
        HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
};