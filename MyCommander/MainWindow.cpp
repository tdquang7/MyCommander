#include "MainWindow.h"
#include "resource.h"
#include "AboutDialog.h"

bool MainWindow::Register(HINSTANCE hInstance, const wchar_t* className) {
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYCOMMANDER));
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = className;
    wc.lpszMenuName = MAKEINTRESOURCEW(IDC_MYCOMMANDER);

    return RegisterClassExW(&wc);
}

HWND MainWindow::Create(HINSTANCE hInstance,
    const wchar_t* className,
    const wchar_t* title) {
    auto* window = new MainWindow(hInstance);

    HWND hwnd = CreateWindowW(
        className, title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        nullptr, nullptr, hInstance, window);
    if (!hwnd) {
        DWORD error = GetLastError();
        delete window;
        return nullptr;
    }
    return hwnd;
}

MainWindow::MainWindow(HINSTANCE hInst)
    : _hInstance(hInst) {
}

LRESULT CALLBACK MainWindow::WndProc(
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    MainWindow* window = nullptr;

    if (msg == WM_NCCREATE) {
        auto cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        window = new MainWindow(cs->hInstance);
        SetWindowLongPtr(hwnd, GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(window));
        window->_hwnd = hwnd;

    }
    else {
        window = reinterpret_cast<MainWindow*>(
            GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (window) {
        return window->HandleMessage(msg, wParam, lParam);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT MainWindow::HandleMessage(
    UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {
    case WM_CREATE:
		return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDM_ABOUT:
            AboutDialog::Show(_hInstance);
            break;
        case IDM_EXIT:
            PostQuitMessage(0);
            break;
        }
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_hwnd, &ps);
        EndPaint(_hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(_hwnd, msg, wParam, lParam);
}