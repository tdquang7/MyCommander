#pragma once
#include "BaseWindow.h"
#include "AboutDialog.h"
#include "Resource.h"
#include  "WinApp.h"

class MainWindow: public BaseWindow {
protected:
    LPCWSTR ClassName() const override;

    void OnCreate() override;
    void OnPaint() override;
    void OnCommand(WPARAM wParam, LPARAM lParam) override;

    void OnHelpAbout(WPARAM wParam, LPARAM lParam);
    void OnFileExit(WPARAM wParam, LPARAM lParam);
};