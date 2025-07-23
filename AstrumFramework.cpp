#include "AstrumFramework.hpp"
#include <thread>
#include <windows.h>
#include <chrono>

AstrumFramework::AstrumFramework() { }

bool AstrumFramework::IsInitialized() const {
    return AstrumWindow::Instance().GetHandle() != nullptr;
}

bool AstrumFramework::IsRunning() const {
    return isRunning;
}

void AstrumFramework::Initialize(const std::wstring& title, unsigned int width, unsigned int height)
{
    AstrumWindow::Instance().Intialize(title, width, height); //winapi 초기화
    AstrumRenderer::Instance().Initialize(width, height); //dx11 초기화
	AstrumDirectInput::Instance().Initialize(); // direct input 초기화
}

int AstrumFramework::Run() {
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

void AstrumFramework::Stop() {
    isRunning = false;
}

void AstrumFramework::Prepare() {
    AstrumChrono::Instance().Initialize();
    RootObject->Prepare();
}

void AstrumFramework::Update() {
    if (!AstrumChrono::Instance().IsUpdateNow()) return;

    AstrumDirectInput::Instance().Update();
    RootObject->Update();
    AstrumCollisionSystem::Instance().Update();
    RootObject->Draw();
    AstrumRenderer::Instance().Rendering();
}

void AstrumFramework::Release() {
    RootObject->Release();
    AstrumDirectInput::Instance().Dispose();
    AstrumChrono::Instance().Dispose();
    AstrumRenderer::Instance().Dispose();
    AstrumWindow::Instance().Dispose();
}