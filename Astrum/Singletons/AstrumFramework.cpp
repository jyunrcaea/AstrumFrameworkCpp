#include "AstrumFramework.hpp"
#include <thread>
#include <windows.h>
#include <chrono>
#include "../AstrumException.hpp"
#include "AstrumCollisionSystem.hpp"
#include "AstrumWindow.hpp"
#include "AstrumRenderer.hpp"
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

bool AstrumFrameworkSingleton::Initialize(const std::wstring& title, unsigned int width, unsigned int height)
{
    if (
        false == AstrumWindow::Initialize(title, width, height) || //winapi 초기화
        false == AstrumRenderer::Instance().Initialize(width, height) //dx11 초기화
    ) return false; 
    AstrumSoundManager::Initialize(); // fmod 초기화
    AstrumChrono::Initialize();
    return true;
}

int AstrumFrameworkSingleton::Run() {
    if (!IsInitialized()) {
        AstrumException(__LINE__, __FILE__, "Framework is not initialized.").Alert();
        return 0;
    }
    if (isRunning) {
        AstrumException(__LINE__, __FILE__, "Framework is already running.").Alert();
        return 0;
    }

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

    AstrumRawInput::Update();
    AstrumKeyBinder::Update();
    RootObject->Update();
    AstrumCollisionSystemSingleton::Instance().Update();
    RootObject->Draw();
    AstrumRenderer::Instance().Rendering();

    AstrumRawInput::Clear();
}

void AstrumFrameworkSingleton::Release() {
    RootObject->Release();
    AstrumChrono::Dispose();
    AstrumRenderer::Instance().Dispose();
    AstrumWindow::Dispose();
    AstrumSoundManager::Dispose();
}