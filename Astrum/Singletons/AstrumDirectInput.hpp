#pragma once
#include <dinput.h>
#include <cstdint>
#include <windows.h>
#include <wrl/client.h>
#include "AstrumSingleton.hpp"
#include "AstrumWindow.hpp"
#include "../AstrumException.hpp"

namespace Astrum {
	enum MouseButtonType
	{
		MouseButtonType_Left = 0,
		MouseButtonType_Right,
		MouseButtonType_Center,
		MouseButtonType_Last,
	};

	class DirectInputSingleton : public Singleton<DirectInputSingleton> {
		friend class Singleton<DirectInputSingleton>;
		friend class DirectInput;

		DirectInputSingleton();
	private:
		bool Initialize();
		void Prepare();
		void Update();
		void Release();
		void Dispose();

		bool IsKeyPressed(uint8_t vk) const;
		bool IsKeyReleased(uint8_t vk) const;
		bool WasKeyPressed(uint8_t vk) const;
		bool WasKeyReleased(uint8_t vk) const;

		Vector2 GetMousePosition() const;
		bool IsMouseKeyPressed(MouseButtonType button) const;
		long GetMouseWheelDelta() const;

		bool IsEnable() const { return isAcquire; }
		bool IsInitialized() const { return dinput; }

		Vector2 GetMouseMovement() const;
	private:
		void UpdateMousePosition();
		HRESULT SetCooperative(IDirectInputDevice8* dev);

		Microsoft::WRL::ComPtr<IDirectInput8> dinput = nullptr;
		Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard = nullptr;
		Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse = nullptr;

		BYTE keyState[256]{};
		BYTE previousKeyState[256]{};
		DIMOUSESTATE mouseState{};

		Vector2 mouseMovement;
		Vector2 mousePosition;
		bool isAcquire = false;
	};

	class DirectInput {
		DirectInput() = delete;

	public:
		static inline bool Initialize() { return DirectInputSingleton::Instance().Initialize(); }
		static inline void Prepare() { DirectInputSingleton::Instance().Prepare(); }
		static inline void Update() { DirectInputSingleton::Instance().Update(); }
		static inline void Release() { DirectInputSingleton::Instance().Release(); }
		static inline void Dispose() { DirectInputSingleton::Instance().Dispose(); }

		static inline bool IsKeyPressed(uint8_t vk) { return DirectInputSingleton::Instance().IsKeyPressed(vk); }
		static inline bool IsKeyReleased(uint8_t vk) { return DirectInputSingleton::Instance().IsKeyReleased(vk); }
		static inline bool WasKeyPressed(uint8_t vk) { return DirectInputSingleton::Instance().WasKeyPressed(vk); }
		static inline bool WasKeyReleased(uint8_t vk) { return DirectInputSingleton::Instance().WasKeyReleased(vk); }

		static inline Vector2 GetMousePosition() { return DirectInputSingleton::Instance().GetMousePosition(); }
		static inline bool IsMouseKeyPressed(MouseButtonType button) { return DirectInputSingleton::Instance().IsMouseKeyPressed(button); }
		static inline long GetMouseWheelDelta() { return DirectInputSingleton::Instance().GetMouseWheelDelta(); }

		static inline bool IsEnable() { return DirectInputSingleton::Instance().IsEnable(); }
		static inline bool IsInitialized() { return DirectInputSingleton::Instance().IsInitialized(); }

		static inline Vector2 GetMouseMovement() { return DirectInputSingleton::Instance().GetMouseMovement(); }
	};
}