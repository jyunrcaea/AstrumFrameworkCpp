#include "AstrumFramework.hpp"
#include <thread>
#include <windows.h>
#include <chrono>
#include "../AstrumException.hpp"
#include "AstrumCollisionSystem.hpp"
#include "AstrumWindow.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumDirectInput.hpp"
#include "AstrumChrono.hpp"
#include "AstrumSoundManager.hpp"
#include "AstrumKeyBinder.hpp"
#include "AstrumRawInput.hpp"
#include "../Resources/AstrumSound.hpp"

AstrumFrameworkSingleton::AstrumFrameworkSingleton() { }

bool AstrumFrameworkSingleton::IsInitialized() const {
    return AstrumWindow::GetHandle() != nullptr;
}

bool AstrumFrameworkSingleton::IsRunning() const {
    return isRunning;
}

void AstrumFrameworkSingleton::Initialize(const std::wstring& title, unsigned int width, unsigned int height)
{
    AstrumWindow::Initialize(title, width, height); //winapi 초기화
    AstrumRenderer::Instance().Initialize(width, height); //dx11 초기화
    AstrumDirectInput::Initialize(); // direct input 초기화
    AstrumSoundManager::Initialize(); // fmod 초기화
    AstrumChrono::Initialize();
}

int AstrumFrameworkSingleton::Run() {
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

void AstrumFrameworkSingleton::Stop() {
    isRunning = false;
}

void AstrumFrameworkSingleton::Prepare() {
    AstrumChrono::Initialize();
    RootObject->Prepare();
}

void AstrumFrameworkSingleton::Update() {
    if (!AstrumChrono::IsUpdateNow()) return;

    AstrumDirectInput::Update();
    AstrumKeyBinder::Update();
    RootObject->Update();
    AstrumCollisionSystemSingleton::Instance().Update();
    RootObject->Draw();
    AstrumRenderer::Instance().Rendering();

    AstrumRawInput::Clear();
}

void AstrumFrameworkSingleton::Release() {
    RootObject->Release();
    AstrumDirectInput::Dispose();
    AstrumChrono::Dispose();
    AstrumRenderer::Instance().Dispose();
    AstrumWindow::Dispose();
    AstrumSoundManager::Dispose();
}