#pragma once
#include <string>
#include <windows.h>
#include "AstrumSingleton.hpp"
#include "../Units/AstrumColor.hpp"
#include "../AstrumException.hpp"
#include "../Vectors/AstrumVector2.hpp"

namespace Astrum {
	struct WindowClientSize
	{
		long long Width;
		long long Height;
	};

	class Window;

	class WindowSingleton : public Singleton<WindowSingleton> {
		friend class Singleton<WindowSingleton>;
		friend class Window;
		WindowSingleton();

	private:
		void Initialize(const std::wstring& title, unsigned int width, unsigned int height);
		void Dispose();

		int GetWidth() const;
		int GetHeight() const;
		bool IsFullscreen() const;

		std::wstring GetTitle() const;
		void SetTitle(const std::wstring& title) const;
		std::wstring GetClassName() const;

		std::pair<int, int> GetPosition() const;
		void SetPosition(int x, int y) const;

		std::pair<int, int> GetSize() const;
		void SetSize(int w, int h);

		void Maximize() const;
		void Minimize() const;
		void Restore() const;

		WindowClientSize GetClientSize() const;

		HWND GetHandle() const;
		HINSTANCE GetInstanceHandle() const;

		bool StopWhenClose = true;
		Color BackgroundColor = Color::White;

	private:
		HWND handle = nullptr;
		HINSTANCE instanceHandle = nullptr;
		std::wstring className;
		int width = 0;
		int height = 0;
		bool isFullscreen = false;

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

	class Window {
		Window() = delete;
	public:
		static inline void Initialize(const std::wstring& title, unsigned int width, unsigned int height) { WindowSingleton::Instance().Initialize(title, width, height); }
		static inline void Dispose() { WindowSingleton::Instance().Dispose(); }

		static inline int GetWidth() { return WindowSingleton::Instance().GetWidth(); }
		static inline int GetHeight() { return WindowSingleton::Instance().GetHeight(); }
		static inline bool IsFullscreen() { return WindowSingleton::Instance().IsFullscreen(); }

		static inline std::wstring GetTitle() { return WindowSingleton::Instance().GetTitle(); }
		static inline void SetTitle(const std::wstring& title) { WindowSingleton::Instance().SetTitle(title); }
		static inline std::wstring GetClassName() { return WindowSingleton::Instance().GetClassName(); }

		static inline std::pair<int, int> GetPosition() { return WindowSingleton::Instance().GetPosition(); }
		static inline void SetPosition(int x, int y) { WindowSingleton::Instance().SetPosition(x, y); }

		static inline std::pair<int, int> GetSize() { return WindowSingleton::Instance().GetSize(); }
		static inline void SetSize(int w, int h) { WindowSingleton::Instance().SetSize(w, h); }

		static inline void Maximize() { WindowSingleton::Instance().Maximize(); }
		static inline void Minimize() { WindowSingleton::Instance().Minimize(); }
		static inline void Restore() { WindowSingleton::Instance().Restore(); }

		static inline WindowClientSize GetClientSize() { return WindowSingleton::Instance().GetClientSize(); }

		static inline HWND GetHandle() { return WindowSingleton::Instance().GetHandle(); }
		static inline HINSTANCE GetInstanceHandle() { return WindowSingleton::Instance().GetInstanceHandle(); }

		static inline bool& StopWhenClose() { return WindowSingleton::Instance().StopWhenClose; }
		static inline Color& BackgroundColor() { return WindowSingleton::Instance().BackgroundColor; }
	};
}
