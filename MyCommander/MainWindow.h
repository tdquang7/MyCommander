#pragma once
#include "BaseWindow.h"
#include "AboutDialog.h"
#include "Resource.h"
#include  "WinApp.h"

class MainWindow: public BaseWindow {
protected:
    LPCWSTR ClassName() const override;

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) override;
    void OnPaint(HWND hwnd) override;
    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) override;

    void OnHelpAbout();
    void OnFileExit();
};