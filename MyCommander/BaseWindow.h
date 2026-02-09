#pragma once
#pragma once
#include <windows.h>

class BaseWindow {
public:
    BaseWindow() = default;
    virtual ~BaseWindow() = default;

    bool Create(
        LPCWSTR windowName,
        DWORD style,
        DWORD exStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int width = CW_USEDEFAULT,
        int height = CW_USEDEFAULT,
        HWND parent = nullptr,
        HMENU menu = nullptr
    );

    HWND Handle() const { return _hwnd; }
    void Show(int cmdShow = SW_SHOW);

public:
    void SetIcon(int id);
    void SetIconSmall(int id);
    void SetMainMenu(int id);
protected:
    virtual LPCWSTR ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT msg, WPARAM wp, LPARAM lp);

    virtual void OnCreate() {}
    virtual void OnDestroy() { PostQuitMessage(0); }
    virtual void OnPaint() {}
    virtual void OnCommand(WPARAM, LPARAM) {}

protected:
    HWND _hwnd = nullptr;

private:
    static LRESULT CALLBACK WindowProcSetup(
        HWND hwnd, UINT msg, WPARAM wp, LPARAM lp
    );

    static LRESULT CALLBACK WindowProcThunk(
        HWND hwnd, UINT msg, WPARAM wp, LPARAM lp
    );
};

// TODO: Dùng mapping của WindowsX.h để làm gọn các macro xử lý message
#define COMMAND(id, handler) \
    if (LOWORD(wParam) == id) return handler(wParam, lParam);