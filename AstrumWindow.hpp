#pragma once
#include "singleton.hpp"
#include "AstrumColor.hpp"
#include <string>
#include <windows.h>

class AstrumWindow : public singleton<AstrumWindow> {
    friend class singleton<AstrumWindow>;

public:
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    bool IsFullscreen() const { return isFullscreen; }

    std::wstring GetTitle() const {
        wchar_t buffer[256];
        GetWindowTextW(handle, buffer, 256);
        return buffer;
    }

    void SetTitle(const std::wstring& title) {
        SetWindowTextW(handle, title.c_str());
    }

    std::wstring GetClassName() const { return className; }

    std::pair<int, int> GetPosition() const {
        RECT rect{};
        GetWindowRect(handle, &rect);
        return { rect.left, rect.top };
    }

    void SetPosition(int x, int y) {
        SetWindowPos(handle, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    std::pair<int, int> GetSize() const {
        RECT rect{};
        GetWindowRect(handle, &rect);
        return { rect.right - rect.left, rect.bottom - rect.top };
    }

    void SetSize(int w, int h) {
        width = w;
        height = h;
        SetWindowPos(handle, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
    }

    void Maximize() const { ShowWindow(handle, SW_MAXIMIZE); }
    void Minimize() const { ShowWindow(handle, SW_MINIMIZE); }
    void Restore() const { ShowWindow(handle, SW_RESTORE); }

    void Intialize(const std::wstring& title, uint16_t width, uint16_t height);
    void Dispose();

    HWND GetHandle() const { return handle; }
    HINSTANCE GetInstanceHandle() const { return instanceHandle; }

    bool StopWhenClose = true;
    AstrumColor BackgroundColor = AstrumColor::White;

private:
    HWND handle = nullptr;
    HINSTANCE instanceHandle = nullptr;
    std::wstring className;
    int width = 0;
    int height = 0;
    bool isFullscreen = false;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
