#pragma once
#include <windows.h>

class MainWindow {
public:
    static bool Register(HINSTANCE hInstance, const wchar_t* className);
    static HWND Create(HINSTANCE hInstance,
        const wchar_t* className,
        const wchar_t* title);

private:
    MainWindow(HINSTANCE hInst);
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

    static LRESULT CALLBACK WndProc(
        HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    HINSTANCE _hInstance;
	HWND _hwnd = nullptr;
};