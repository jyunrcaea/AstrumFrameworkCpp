#pragma once
#include <string>
#include <windows.h>
#include "AstrumSingleton.hpp"
#include "../Units/AstrumColor.hpp"
#include "../AstrumException.hpp"
#include "../Vectors/AstrumVector2.hpp"

struct AstrumWindowClientSize
{
    long long Width;
    long long Height;
};

class AstrumWindowSingleton : public AstrumSingleton<AstrumWindowSingleton> {
    friend class AstrumSingleton<AstrumWindowSingleton>;
    friend class AstrumWindow;
    AstrumWindowSingleton();

private:
    bool Initialize(const std::wstring& title, unsigned int width, unsigned int height);
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

    AstrumWindowClientSize GetClientSize() const;

    HWND GetHandle() const;
    HINSTANCE GetInstanceHandle() const;

    bool StopWhenClose = true;
    AstrumColor BackgroundColor = AstrumColor::White;

private:
    HWND handle = nullptr;
    HINSTANCE instanceHandle = nullptr;
    std::wstring className;
    int width = 0;
    int height = 0;
    bool isFullscreen = false;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

/// <summary>
/// Windows API를 통해 창을 관리하는 정적 헬퍼 클래스입니다.
/// </summary>
class AstrumWindow {
    AstrumWindow() = delete;
public:
    /// <summary>
    /// 지정된 제목과 크기로 Windows API를 통해 창을 초기화합니다.
    /// </summary>
    /// <param name="title">창 제목으로 사용할 와이드 문자열(std::wstring).</param>
    /// <param name="width">창 너비 (픽셀 단위).</param>
    /// <param name="height">창 높이 (픽셀 단위).</param>
    /// <returns>창 초기화에 성공하면 true, 그렇지 않으면 false를 반환합니다.</returns>
    static inline bool Initialize(const std::wstring& title, unsigned int width, unsigned int height) {
        return AstrumWindowSingleton::Instance().Initialize(title, width, height);
    }

    /// <summary>
    /// 창을 해제하고 리소스를 정리합니다.
    /// </summary>
    static inline void Dispose() {
        AstrumWindowSingleton::Instance().Dispose();
    }

    /// <summary>
    /// 현재 창의 너비를 반환합니다.
    /// </summary>
    /// <returns>창의 너비를 정수(int) 값으로 반환합니다. (픽셀 단위)</returns>
    static inline int GetWidth() {
        return AstrumWindowSingleton::Instance().GetWidth();
    }

    /// <summary>
    /// 현재 창의 높이를 반환합니다.
    /// </summary>
    /// <returns>창의 높이를 정수(int) 값으로 반환합니다. (일반적으로 픽셀 단위)</returns>
    static inline int GetHeight() {
        return AstrumWindowSingleton::Instance().GetHeight();
    }

    /// <summary>
    /// 창이 현재 전체화면(Fullscreen) 모드인지 여부를 반환합니다.
    /// </summary>
    /// <returns>전체화면 모드이면 true, 그렇지 않으면 false를 반환합니다.</returns>
    static inline bool IsFullscreen() {
        return AstrumWindowSingleton::Instance().IsFullscreen();
    }

    /// <summary>
    /// 현재 창 제목을 조회하여 반환합니다.
    /// </summary>
    /// <returns>AstrumWindowSingleton::Instance().GetTitle() 에서 반환한 제목의 복사본(std::wstring)을 반환합니다.</returns>
    static inline std::wstring GetTitle() {
        return AstrumWindowSingleton::Instance().GetTitle();
    }

    /// <summary>
    /// 와이드 문자열 제목을 전달하여 창 제목을 설정합니다.
    /// </summary>
    /// <param name="title">새 창 제목 (std::wstring 타입).</param>
    static inline void SetTitle(const std::wstring& title) {
        AstrumWindowSingleton::Instance().SetTitle(title);
    }

    /// <summary>
    /// 창 클래스 이름을 반환합니다.
    /// </summary>
    /// <returns>AstrumWindowSingleton로부터 가져온 창 클래스 이름(std::wstring)을 반환합니다.</returns>
    static inline std::wstring GetClassName() {
        return AstrumWindowSingleton::Instance().GetClassName();
    }

    /// <summary>
    /// 현재 창 위치를 반환합니다.
    /// </summary>
    /// <returns>창 위치 좌표(x, y)를 담은 std::pair<int, int> 를 반환합니다.</returns>
    static inline std::pair<int, int> GetPosition() {
        return AstrumWindowSingleton::Instance().GetPosition();
    }

    /// <summary>
    /// 창 위치를 설정합니다.
    /// </summary>
    /// <param name="x">새 창 위치의 X 좌표.</param>
    /// <param name="y">새 창 위치의 Y 좌표.</param>
    static inline void SetPosition(int x, int y) {
        AstrumWindowSingleton::Instance().SetPosition(x, y);
    }

    /// <summary>
    /// 현재 창 크기를 가져옵니다.
    /// </summary>
    /// <returns>std::pair<int,int> 형식으로 (너비, 높이)를 반환합니다. (일반적으로 픽셀 단위)</returns>
    static inline std::pair<int, int> GetSize() {
        return AstrumWindowSingleton::Instance().GetSize();
    }

    /// <summary>
    /// 창 크기를 설정합니다.
    /// </summary>
    /// <param name="w">새 창의 너비.</param>
    /// <param name="h">새 창의 높이.</param>
    static inline void SetSize(int w, int h) {
        AstrumWindowSingleton::Instance().SetSize(w, h);
    }

    /// <summary>
    /// 창을 최대화합니다.
    /// </summary>
    static inline void Maximize() {
        AstrumWindowSingleton::Instance().Maximize();
    }

    /// <summary>
    /// 창을 최소화합니다.
    /// </summary>
    static inline void Minimize() {
        AstrumWindowSingleton::Instance().Minimize();
    }

    /// <summary>
    /// 창을 복원합니다.
    /// </summary>
    static inline void Restore() {
        AstrumWindowSingleton::Instance().Restore();
    }

    /// <summary>
    /// 클라이언트(렌더링) 영역 크기를 반환합니다.
    /// </summary>
    /// <returns>AstrumWindowSingleton 인스턴스에서 가져온 클라이언트 영역의 너비/높이를 나타내는 AstrumWindowClientSize 값을 반환합니다.</returns>
    static inline AstrumWindowClientSize GetClientSize() {
        return AstrumWindowSingleton::Instance().GetClientSize();
    }

    /// <summary>
    /// 네이티브 윈도우 핸들(HWND)을 반환합니다.
    /// </summary>
    /// <returns>AstrumWindowSingleton::Instance().GetHandle() 에서 가져온 HWND 핸들을 반환합니다. 창이 없으면 NULL일 수 있습니다.</returns>
    static inline HWND GetHandle() {
        return AstrumWindowSingleton::Instance().GetHandle();
    }

    /// <summary>
    /// 창의 인스턴스 핸들(HINSTANCE)을 반환합니다.
    /// </summary>
    /// <returns>애플리케이션 인스턴스 핸들.</returns>
    static inline HINSTANCE GetInstanceHandle() {
        return AstrumWindowSingleton::Instance().GetInstanceHandle();
    }

    /// <summary>
    /// 창이 닫혔을 때 애플리케이션을 자동 종료할지에 대한 플래그를 참조로 반환합니다.
    /// </summary>
    static inline bool& StopWhenClose() {
        return AstrumWindowSingleton::Instance().StopWhenClose;
    }

    /// <summary>
    /// 창의 배경 색상 객체를 참조로 반환합니다.
    /// </summary>
    static inline AstrumColor& BackgroundColor() {
        return AstrumWindowSingleton::Instance().BackgroundColor;
    }
};

