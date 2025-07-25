#pragma once
#include "singleton.hpp"
#include "AstrumColor.hpp"
#include "AstrumException.hpp"
#include <string>
#include <windows.h>

class AstrumWindow : public Singleton<AstrumWindow> {
    friend class Singleton<AstrumWindow>;

public:
    int GetWidth() const;
    int GetHeight() const;
    bool IsFullscreen() const;

    std::wstring GetTitle() const;
    void SetTitle(const std::wstring& title);
    std::wstring GetClassName() const;

    std::pair<int, int> GetPosition() const;
    void SetPosition(int x, int y);

    std::pair<int, int> GetSize() const;
    void SetSize(int w, int h);

    void Maximize() const;
    void Minimize() const;
    void Restore() const;

    void Intialize(const std::wstring& title, uint16_t width, uint16_t height);
    void Dispose();

    HWND GetHandle() const;
    HINSTANCE GetInstanceHandle() const;

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
