#pragma once
#include <string>
#include <windows.h>
#include "AstrumSingleton.hpp"
#include "../Units/AstrumColor.hpp"
#include "../AstrumException.hpp"
#include "../Vectors/AstrumVector2.hpp"

struct AstrumWindowClientSize
{
    long long Width;
    long long Height;
};

class AstrumWindowSingleton : public AstrumSingleton<AstrumWindowSingleton> {
    friend class AstrumSingleton<AstrumWindowSingleton>;
    friend class AstrumWindow;
    AstrumWindowSingleton();

private:
    void Initialize(const std::wstring& title, unsigned int width, unsigned int height);
    void Dispose();

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

    AstrumWindowClientSize GetClientSize() const;

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

class AstrumWindow {
    AstrumWindow() = delete;
public:
    static inline void Initialize(const std::wstring& title, unsigned int width, unsigned int height) { AstrumWindowSingleton::Instance().Initialize(title, width, height); }
    static inline void Dispose() { AstrumWindowSingleton::Instance().Dispose(); }

    static inline int GetWidth() { return AstrumWindowSingleton::Instance().GetWidth(); }
    static inline int GetHeight() { return AstrumWindowSingleton::Instance().GetHeight(); }
    static inline bool IsFullscreen() { return AstrumWindowSingleton::Instance().IsFullscreen(); }

    static inline std::wstring GetTitle() { return AstrumWindowSingleton::Instance().GetTitle(); }
    static inline void SetTitle(const std::wstring& title) { AstrumWindowSingleton::Instance().SetTitle(title); }
    static inline std::wstring GetClassName() { return AstrumWindowSingleton::Instance().GetClassName(); }

    static inline std::pair<int, int> GetPosition() { return AstrumWindowSingleton::Instance().GetPosition(); }
    static inline void SetPosition(int x, int y) { AstrumWindowSingleton::Instance().SetPosition(x, y); }

    static inline std::pair<int, int> GetSize() { return AstrumWindowSingleton::Instance().GetSize(); }
    static inline void SetSize(int w, int h) { AstrumWindowSingleton::Instance().SetSize(w, h); }

    static inline void Maximize() { AstrumWindowSingleton::Instance().Maximize(); }
    static inline void Minimize() { AstrumWindowSingleton::Instance().Minimize(); }
    static inline void Restore() { AstrumWindowSingleton::Instance().Restore(); }

    static inline AstrumWindowClientSize GetClientSize() { return AstrumWindowSingleton::Instance().GetClientSize(); }

    static inline HWND GetHandle() { return AstrumWindowSingleton::Instance().GetHandle(); }
    static inline HINSTANCE GetInstanceHandle() { return AstrumWindowSingleton::Instance().GetInstanceHandle(); }

    static inline bool& StopWhenClose() { return AstrumWindowSingleton::Instance().StopWhenClose; }
    static inline AstrumColor& BackgroundColor() { return AstrumWindowSingleton::Instance().BackgroundColor; }
};
