#pragma once
#include <windows.h>
#include <format>

#ifdef _DEBUG

#define DebugFomat(message, ...)                                         \
    do {                                                               \
        auto msg = std::format(L"[LOG] " message L"\n", __VA_ARGS__);  \
        OutputDebugStringW(msg.c_str());                               \
    } while (0)

#define DebugLog(message) OutputDebugStringW(message);  

#else
#define DebugFomat(message, ...) ((void)0)
#define DebugLog(message) ((void)0)
#endif