#pragma once
#include <windows.h>
#include <memory>
#include <string>
#include <cstdint>
#include "../Objects/AstrumGroupObject.hpp"
#include "AstrumSingleton.hpp"

class AstrumFrameworkSingleton : public AstrumSingleton<AstrumFrameworkSingleton> {
    friend class AstrumSingleton<AstrumFrameworkSingleton>;
    friend class AstrumFramework;
    AstrumFrameworkSingleton();

private:
    bool IsInitialized() const;
    bool IsRunning() const;
    bool Initialize(const std::wstring& title = L"Astrum Framework", unsigned int width = 1280, unsigned int height = 720);
    int Run();
    void Stop();
    std::shared_ptr<AstrumGroupObject> RootObject = std::make_shared<AstrumGroupObject>();

private:
    bool isRunning = false;
    void Prepare();
    void Update();
    void Release();
};

/// <summary>
/// 전역 Astrum 프레임워크 싱글톤과 상호작용하기 위한 정적 헬퍼를 제공합니다. 인스턴스화할 수 없는 클래스(생성자 삭제)이며, AstrumFrameworkSingleton::Instance()로 호출을 전달합니다.
/// </summary>
class AstrumFramework {
    AstrumFramework() = delete;
public:
    /// <summary>
    /// Astrum 프레임워크 싱글톤이 초기화되었는지 확인합니다.
    /// </summary>
    /// <returns>초기화되었으면 true, 아니면 false</returns>
    static inline bool IsInitialized() { return AstrumFrameworkSingleton::Instance().IsInitialized(); }
    /// <summary>
    /// Astrum 프레임워크가 현재 실행 중인지 확인합니다.
    /// </summary>
    /// <returns>실행 중이면 true, 아니면 false</returns>
    static inline bool IsRunning() { return AstrumFrameworkSingleton::Instance().IsRunning(); }
    /// <summary>
    /// Astrum 프레임워크 싱글톤을 윈도우 제목과 초기 크기로 초기화합니다.
    /// </summary>
    /// <param name="title">윈도우 제목 (기본값: "Astrum Framework")</param>
    /// <param name="width">초기 윈도우 너비(픽셀, 기본값: 1280)</param>
    /// <param name="height">초기 윈도우 높이(픽셀, 기본값: 720)</param>
    static inline void Initialize(const std::wstring& title = L"Astrum Framework", unsigned int width = 1280, unsigned int height = 720) { AstrumFrameworkSingleton::Instance().Initialize(title, width, height); }
    /// <summary>
    /// AstrumFrameworkSingleton 인스턴스의 Run()을 호출하고 결과를 반환합니다.
    /// </summary>
    /// <returns>AstrumFrameworkSingleton::Instance().Run()이 반환하는 상태 코드</returns>
    static inline int Run() { return AstrumFrameworkSingleton::Instance().Run(); }
    /// <summary>
    /// 프레임워크를 중지합니다.
    /// </summary>
    static inline void Stop() { AstrumFrameworkSingleton::Instance().Stop(); }
    /// <summary>
    /// 프레임워크의 루트 AstrumGroupObject를 반환합니다.
    /// </summary>
    /// <returns>현재 루트 객체의 공유 포인터</returns>
    static inline std::shared_ptr<AstrumGroupObject> GetRootObject() { return AstrumFrameworkSingleton::Instance().RootObject; }
    /// <summary>
    /// 프레임워크의 루트 객체를 설정합니다.
    /// </summary>
    /// <param name="obj">설정할 AstrumGroupObject의 공유 포인터</param>
    static inline void SetRootObject(const std::shared_ptr<AstrumGroupObject>& obj) { AstrumFrameworkSingleton::Instance().RootObject = obj; }
};