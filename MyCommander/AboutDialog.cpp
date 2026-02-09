#include "AboutDialog.h"

void AboutDialog::Show() {
    DialogBox(WinApp::Current().Instance(),
        MAKEINTRESOURCE(IDD_ABOUTBOX),
        nullptr,
        DialogProc);
}

INT_PTR CALLBACK AboutDialog::DialogProc(
    HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_COMMAND &&
        (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)) {
        EndDialog(hDlg, LOWORD(wParam));
        return TRUE;
    }
    return FALSE;
}
