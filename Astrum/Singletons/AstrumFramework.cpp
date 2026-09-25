#include "AstrumFramework.hpp"
#include <thread>
#include <windows.h>
#include <timeapi.h>
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

// timeBeginPeriod / timeEndPeriod
#pragma comment(lib, "winmm.lib")

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

    // 대기(Sleep) 정밀도를 1ms로 높입니다. (기본값은 약 15.6ms라 프레임 제한 시 프레임이 튈 수 있음)
    timeBeginPeriod(1);

    MSG msg{};
    int exitCode = 0;
    while (isRunning) {
        // 1. 쌓여있는 메시지를 모두 처리합니다. (입력이 많아도 프레임이 밀리지 않도록 한번에 비움)
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == msg.message) {
                exitCode = static_cast<int>(msg.wParam);
                isRunning = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (false == isRunning) break;

        // 2. 업데이트 시점이면 한 프레임을 진행합니다.
        if (AstrumChrono::IsUpdateNow()) {
            Update();
            continue;
        }

        // 3. 다음 프레임까지 CPU를 쉬게 합니다. 그 사이 메시지(입력)가 들어오면 즉시 깨어납니다.
        //    (예전에는 이 구간을 쉬지 않고 반복해서 CPU 코어 하나를 100% 사용했습니다.)
        const auto remaining = std::chrono::duration_cast<std::chrono::milliseconds>(AstrumChrono::GetTimeUntilNextUpdate()).count();
        if (remaining >= 2) {
            // 깨어나는 시간이 늦어지지 않도록 1ms 일찍 깨어나고, 나머지는 아래에서 짧게 양보하며 기다립니다.
            MsgWaitForMultipleObjectsEx(0, nullptr, static_cast<DWORD>(remaining - 1), QS_ALLINPUT, MWMO_INPUTAVAILABLE);
        }
        else {
            std::this_thread::yield();
        }
    }

    timeEndPeriod(1);

    Release();

    return exitCode;
}

void AstrumFrameworkSingleton::Stop() {
    isRunning = false;
}

void AstrumFrameworkSingleton::Prepare() {
    AstrumChrono::Initialize();
    RootObject->Prepare();
}

void AstrumFrameworkSingleton::Update() {
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