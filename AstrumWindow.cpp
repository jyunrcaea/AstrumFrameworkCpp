#include "AstrumWindow.hpp"
#include "AstrumFramework.hpp"
#include "AstrumChrono.hpp"
#include "AstrumDirectInput.hpp"

void AstrumWindowSingleton::Initialize(const std::wstring& title, uint16_t w, uint16_t h) {
    instanceHandle = GetModuleHandleW(nullptr);
    className = title;

    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.hInstance = instanceHandle;
    wc.lpszClassName = className.c_str();
    wc.lpfnWndProc = WindowProc;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassExW(&wc))
        throw AstrumException("Window class registration failed.");

    width = w;
    height = h;

    handle = CreateWindowExW(
        WS_EX_APPWINDOW, className.c_str(), title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        nullptr, nullptr, instanceHandle, nullptr);

    if (!handle)
        throw AstrumException("Window creation failed.");

    ShowWindow(handle, SW_SHOWNORMAL);
    UpdateWindow(handle);
}

void AstrumWindowSingleton::Dispose() {
    if (!handle)
        throw AstrumException("Window handle is null.");

    DestroyWindow(handle);
    handle = nullptr;
    UnregisterClassW(className.c_str(), instanceHandle);
    instanceHandle = nullptr;
}

LRESULT CALLBACK AstrumWindowSingleton::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_ERASEBKGND: return 1;
    case WM_CLOSE:
        if (AstrumWindowSingleton::Instance().StopWhenClose)
            AstrumFramework::Stop();
        PostQuitMessage(0);
        return 0;
    case WM_SETFOCUS:
        AstrumDirectInput::Prepare();
        break;
    case WM_KILLFOCUS:
        AstrumDirectInput::Release();
        break;
    case WM_ACTIVATE:
        if (LOWORD(wParam) == WA_INACTIVE) AstrumDirectInput::Release();
        else AstrumDirectInput::Prepare();
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int AstrumWindowSingleton::GetWidth() const { return width; }
int AstrumWindowSingleton::GetHeight() const { return height; }
bool AstrumWindowSingleton::IsFullscreen() const { return isFullscreen; }

std::wstring AstrumWindowSingleton::GetTitle() const {
    wchar_t buffer[256];
    GetWindowTextW(handle, buffer, 256);
    return buffer;
}

void AstrumWindowSingleton::SetTitle(const std::wstring& title) {
    SetWindowTextW(handle, title.c_str());
}

std::wstring AstrumWindowSingleton::GetClassName() const { return className; }

std::pair<int, int> AstrumWindowSingleton::GetPosition() const {
    RECT rect{};
    GetWindowRect(handle, &rect);
    return { rect.left, rect.top };
}

void AstrumWindowSingleton::SetPosition(int x, int y) {
    SetWindowPos(handle, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

std::pair<int, int> AstrumWindowSingleton::GetSize() const {
    RECT rect{};
    GetWindowRect(handle, &rect);
    return { rect.right - rect.left, rect.bottom - rect.top };
}

void AstrumWindowSingleton::SetSize(int w, int h) {
    width = w;
    height = h;
    SetWindowPos(handle, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}

void AstrumWindowSingleton::Maximize() const { ShowWindow(handle, SW_MAXIMIZE); }
void AstrumWindowSingleton::Minimize() const { ShowWindow(handle, SW_MINIMIZE); }
void AstrumWindowSingleton::Restore() const { ShowWindow(handle, SW_RESTORE); }

HWND AstrumWindowSingleton::GetHandle() const { return handle; }
HINSTANCE AstrumWindowSingleton::GetInstanceHandle() const { return instanceHandle; }