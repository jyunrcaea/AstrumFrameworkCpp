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
#include "../Resources/AstrumSound.hpp"

namespace Astrum {
	FrameworkSingleton::FrameworkSingleton() { }

	bool FrameworkSingleton::IsInitialized() const {
		return Window::GetHandle() != nullptr;
	}

	bool FrameworkSingleton::IsRunning() const {
		return isRunning;
	}

	void FrameworkSingleton::Initialize(const std::wstring& title, unsigned int width, unsigned int height)
	{
		Window::Initialize(title, width, height); //winapi 초기화
		Renderer::Instance().Initialize(width, height); //dx11 초기화
		DirectInput::Initialize(); // direct input 초기화
		SoundManager::Initialize(); // fmod 초기화
		Chrono::Initialize();
	}

	int FrameworkSingleton::Run() {
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

	void FrameworkSingleton::Stop() {
		isRunning = false;
	}

	void FrameworkSingleton::Prepare() {
		Chrono::Initialize();
		RootObject->Prepare();
	}

	void FrameworkSingleton::Update() {
		if (!Chrono::IsUpdateNow()) return;

		DirectInput::Update();
		KeyBinder::Update();
		RootObject->Update();
		CollisionSystemSingleton::Instance().Update();
		RootObject->Draw();
		Renderer::Instance().Rendering();
	}

	void FrameworkSingleton::Release() {
		RootObject->Release();
		DirectInput::Dispose();
		Chrono::Dispose();
		Renderer::Instance().Dispose();
		Window::Dispose();
		SoundManager::Dispose();
	}
}