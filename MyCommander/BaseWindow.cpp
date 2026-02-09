#include "BaseWindow.h"
#include "Resource.h"
#include "WinApp.h"

bool BaseWindow::Create(
    LPCWSTR windowName,
    DWORD style,
    DWORD exStyle,
    int x, int y, int width, int height,
    HWND parent,
    HMENU menu
) {
    WNDCLASSEXW wc{ sizeof(wc) };
    wc.lpfnWndProc = WindowProcSetup;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = ClassName();
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassExW(&wc);

    _hwnd = CreateWindowExW(
        exStyle,
        ClassName(),
        windowName,
        style,
        x, y, width, height,
        parent,
        menu,
        wc.hInstance,
        this        
    );

    return _hwnd != nullptr;
}

void BaseWindow::Show(int cmdShow) {
    ShowWindow(_hwnd, cmdShow);
    UpdateWindow(_hwnd);
}

LRESULT CALLBACK BaseWindow::WindowProcSetup(
    HWND hwnd, UINT msg, WPARAM wp, LPARAM lp
) {
    if (msg == WM_NCCREATE) {
        auto cs = reinterpret_cast<CREATESTRUCTW*>(lp);
        auto* window = static_cast<BaseWindow*>(cs->lpCreateParams);

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(window)
        );

        window->_hwnd = hwnd;

        SetWindowLongPtrW(
            hwnd,
            GWLP_WNDPROC,
            reinterpret_cast<LONG_PTR>(WindowProcThunk)
        );

        return window->HandleMessage(msg, wp, lp);
    }

    return DefWindowProcW(hwnd, msg, wp, lp);
}

LRESULT CALLBACK BaseWindow::WindowProcThunk(
    HWND hwnd, UINT msg, WPARAM wp, LPARAM lp
) {
    auto* window = reinterpret_cast<BaseWindow*>(
        GetWindowLongPtrW(hwnd, GWLP_USERDATA)
        );

    return window
        ? window->HandleMessage(msg, wp, lp)
        : DefWindowProcW(hwnd, msg, wp, lp);
}

LRESULT BaseWindow::HandleMessage(UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_NCCREATE:
        return TRUE;

    case WM_CREATE:
        OnCreate();
        return 0;

    case WM_COMMAND:
        OnCommand(wp, lp);
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_DESTROY:
        OnDestroy();
        return 0;
    }

    return DefWindowProcW(_hwnd, msg, wp, lp);
}


void BaseWindow::SetIcon(int id) {
    SendMessageW(_hwnd, WM_SETICON, ICON_BIG,
        (LPARAM)LoadIconW(WinApp::Current().Instance(), MAKEINTRESOURCE(id)));
}

void BaseWindow::SetIconSmall(int id) {
    SendMessageW(_hwnd, WM_SETICON, ICON_SMALL,
        (LPARAM)LoadIconW(WinApp::Current().Instance(), MAKEINTRESOURCE(id)));
}

void BaseWindow::SetMainMenu(int id) {
    HMENU hMenu = LoadMenuW(
        WinApp::Current().Instance(),
        MAKEINTRESOURCE(id)
    );
    SetMenu(_hwnd, hMenu);
    DrawMenuBar(_hwnd);
}