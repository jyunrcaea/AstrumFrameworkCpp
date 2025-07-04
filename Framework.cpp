#include "Framework.hpp"
#include <thread>
#include <windows.h>
#include <chrono>

Framework::Framework()
    : isRunning(false),
    RootObject(std::make_shared<AstrumGroupObject>())
{
}

bool Framework::IsInitialized() const {
    return AstrumWindow::Instance().GetHandle() != nullptr;
}

bool Framework::IsRunning() const {
    return isRunning;
}

void Framework::Initialize(const std::wstring& title,
    uint16_t width,
    uint16_t height)
{
    AstrumWindow::Instance().Intialize(title, width, height);
    AstrumRenderer::Instance().Initialize(width, height);
    AstrumDirectInput::Instance().Initialize();
}

int Framework::Run() {
    if (!IsInitialized())
        throw AstrumException("Framework is not initialized.");
    if (isRunning)
        throw AstrumException("Framework is already running.");

    isRunning = true;
    Prepare();

    MSG msg{};
    while (isRunning) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            Update();
        }
    }

    Release();

    return static_cast<int>(msg.wParam);
}

void Framework::Stop() {
    isRunning = false;
}

void Framework::Prepare() {
    AstrumChrono::Instance().Initialize();
    RootObject->Prepare();
}

void Framework::Update() {
    if (!AstrumChrono::Instance().IsUpdateNow()) return;

    AstrumDirectInput::Instance().Update();
    RootObject->Update();
    RootObject->Draw();
    AstrumRenderer::Instance().Rendering();
}

void Framework::Release() {
    RootObject->Release();
    AstrumDirectInput::Instance().Dispose();
    AstrumChrono::Instance().Dispose();
    AstrumRenderer::Instance().Dispose();
    AstrumWindow::Instance().Dispose();
}