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

    virtual BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
    virtual void OnDestroy(HWND hwnd);
    virtual void OnPaint(HWND hwnd);
    virtual void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

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