#include "AstrumWindow.hpp"
#include "AstrumFramework.hpp"
#include "AstrumChrono.hpp"
#include "AstrumRawInput.hpp"
#include "AstrumRenderer.hpp"

namespace {
    constexpr DWORD WindowStyle = WS_OVERLAPPEDWINDOW;
    constexpr DWORD WindowExStyle = WS_EX_APPWINDOW;

    // 클라이언트 영역이 (w, h)가 되도록 테두리/제목 표시줄을 포함한 창 크기를 계산합니다.
    SIZE CalculateWindowSize(int w, int h, DWORD style, DWORD exStyle) {
        RECT rect{ 0, 0, w, h };
        AdjustWindowRectEx(&rect, style, FALSE, exStyle);
        return { rect.right - rect.left, rect.bottom - rect.top };
    }
}

AstrumWindowSingleton::AstrumWindowSingleton() { }

bool AstrumWindowSingleton::Initialize(const std::wstring& title, unsigned int w, unsigned int h) {
#pragma region register class
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

    if (!RegisterClassExW(&wc)) {
        AstrumException("Window class registration failed.").Alert();
        return false;
    }
#pragma endregion

#pragma region create window
    // 요청한 크기가 테두리를 포함한 창 크기가 아닌, 실제 그려지는 클라이언트 영역의 크기가 되도록 합니다.
    width = static_cast<int>(w);
    height = static_cast<int>(h);
    const SIZE windowSize = CalculateWindowSize(width, height, WindowStyle, WindowExStyle);
    handle = CreateWindowExW(
        WindowExStyle, className.c_str(), title.c_str(),
        WindowStyle,
        CW_USEDEFAULT, CW_USEDEFAULT,
        windowSize.cx,
        windowSize.cy,
        nullptr, nullptr, instanceHandle, nullptr);

    if (!handle) {
        AstrumException("Window creation failed.").Alert();
        return false;
    }
#pragma endregion

    ShowWindow(handle, SW_SHOWNORMAL);
    UpdateWindow(handle);

#pragma region raw input
	AstrumRawInput::Initialize();
#pragma endregion

    return true;
}

void AstrumWindowSingleton::Dispose() {
    // Raw Input 장치 등록 해제 (창을 파괴하기 전에 한번만)
	AstrumRawInput::Dispose();

    if (nullptr == handle) {
        AstrumException("Window handle is null.").Alert();
        return;
    }

    DestroyWindow(handle);
    handle = nullptr;
    UnregisterClassW(className.c_str(), instanceHandle);
    instanceHandle = nullptr;
}

LRESULT CALLBACK AstrumWindowSingleton::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_ERASEBKGND: return 1;
    case WM_CLOSE: {
        // StopWhenClose가 false면 창을 닫지 않고 무시합니다. (게임 로직에서 직접 처리)
        if (AstrumWindowSingleton::Instance().StopWhenClose) {
            AstrumFramework::Stop();
            PostQuitMessage(0);
        }
        return 0;
    }
    case WM_INPUT: {
        unsigned int dwSize = 0;
        if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER)) == (UINT)-1) {
            break;
        }
        if (std::vector<unsigned char> buffer(dwSize); GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer.data(), &dwSize, sizeof(RAWINPUTHEADER)) == dwSize) {
            AstrumRawInput::Enqueue(*reinterpret_cast<RAWINPUT*>(buffer.data()));
        }
        return 0;
    }
    case WM_SIZE: {
        // 클라이언트 영역 크기에 맞춰 백버퍼를 다시 만듭니다. (최소화 시에는 크기가 0이므로 무시)
        if (SIZE_MINIMIZED != wParam) {
            AstrumRenderer::Instance().Resize(LOWORD(lParam), HIWORD(lParam));
        }
        break;
    }
    default:
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

void AstrumWindowSingleton::SetTitle(const std::wstring& title) const {
    SetWindowTextW(handle, title.c_str());
}

std::wstring AstrumWindowSingleton::GetClassName() const { return className; }

std::pair<int, int> AstrumWindowSingleton::GetPosition() const {
    RECT rect{};
    GetWindowRect(handle, &rect);
    return { rect.left, rect.top };
}

void AstrumWindowSingleton::SetPosition(int x, int y) const {
    SetWindowPos(handle, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

std::pair<int, int> AstrumWindowSingleton::GetSize() const {
    RECT rect{};
    GetWindowRect(handle, &rect);
    return { rect.right - rect.left, rect.bottom - rect.top };
}

void AstrumWindowSingleton::SetSize(int w, int h) {
    // 클라이언트 영역이 (w, h)가 되도록 창 크기를 계산합니다. (논리 해상도인 width/height는 바꾸지 않음)
    const SIZE windowSize = CalculateWindowSize(w, h,
        static_cast<DWORD>(GetWindowLongPtrW(handle, GWL_STYLE)),
        static_cast<DWORD>(GetWindowLongPtrW(handle, GWL_EXSTYLE)));
    SetWindowPos(handle, nullptr, 0, 0, windowSize.cx, windowSize.cy, SWP_NOMOVE | SWP_NOZORDER);
}

void AstrumWindowSingleton::Maximize() const { ShowWindow(handle, SW_MAXIMIZE); }
void AstrumWindowSingleton::Minimize() const { ShowWindow(handle, SW_MINIMIZE); }
void AstrumWindowSingleton::Restore() const { ShowWindow(handle, SW_RESTORE); }

AstrumWindowClientSize AstrumWindowSingleton::GetClientSize() const {
    RECT windowRect;
    GetClientRect(AstrumWindow::GetHandle(), &windowRect);
    return {
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top
    };
}

HWND AstrumWindowSingleton::GetHandle() const { return handle; }
HINSTANCE AstrumWindowSingleton::GetInstanceHandle() const { return instanceHandle; }