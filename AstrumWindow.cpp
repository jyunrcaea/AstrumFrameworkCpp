#include "AstrumWindow.hpp"
#include "AstrumException.hpp"
#include "Framework.hpp"

void AstrumWindow::Intialize(const std::wstring& title, uint16_t w, uint16_t h) {
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

void AstrumWindow::Dispose() {
    if (!handle)
        throw AstrumException("Window handle is null.");

    DestroyWindow(handle);
    handle = nullptr;
    UnregisterClassW(className.c_str(), instanceHandle);
    instanceHandle = nullptr;
}

LRESULT CALLBACK AstrumWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_ERASEBKGND: return 1;
    case WM_CLOSE:
        if (Instance().StopWhenClose)
            Framework::Instance().Stop();
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
