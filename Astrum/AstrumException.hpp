#pragma once
#include <stdexcept>
#include <string>

/// <summary>
/// Astrum 프레임워크의 예외 클래스입니다.
/// std::runtime_error를 상속받으며, 디버그/릴리스 모드에 따라 다르게 처리됩니다.
/// 디버그 모드에서는 예외를 발생시켜 실행을 중단하고, 릴리스 모드에서는 오류 메시지만 출력합니다.
/// </summary>
class AstrumException : public std::runtime_error {
public:
    /// <summary>
    /// 기본 생성자입니다. 메시지는 "Astrum Exception"입니다.
    /// </summary>
    AstrumException() : std::runtime_error("Astrum Exception") { print(); }
    /// <summary>
    /// 오류 메시지를 지정하여 예외를 생성합니다.
    /// </summary>
    /// <param name="message">오류 메시지입니다. (std::string)</param>
    AstrumException(const std::string& message) : std::runtime_error(message) { print(); }
    /// <summary>
    /// 오류 메시지를 지정하여 예외를 생성합니다. (와이드 문자 버전)
    /// </summary>
    /// <param name="message">오류 메시지입니다. (std::wstring)</param>
    AstrumException(const std::wstring& message) : std::runtime_error(wstr2str(message)) { print(); }
    /// <summary>
    /// 파일 위치 정보와 오류 메시지를 지정하여 예외를 생성합니다.
    /// </summary>
    /// <param name="line">예외가 발생한 줄 번호입니다.</param>
    /// <param name="file">예외가 발생한 파일 이름입니다.</param>
    /// <param name="message">오류 메시지입니다. (std::string)</param>
    AstrumException(const int line, const std::string& file, const std::string& message) : std::runtime_error(message +" (Line: " + std::to_string(line) + ", File: {" + file +"})") { print(); }
    /// <summary>
    /// 파일 위치 정보와 오류 메시지를 지정하여 예외를 생성합니다. (와이드 문자 메시지)
    /// </summary>
    /// <param name="line">예외가 발생한 줄 번호입니다.</param>
    /// <param name="file">예외가 발생한 파일 이름입니다.</param>
    /// <param name="message">오류 메시지입니다. (std::wstring)</param>
    AstrumException(const int line, const std::string& file, const std::wstring& message) : std::runtime_error(wstr2str(message) +" (Line: " + std::to_string(line) + ", File: '" + file + "')") { print(); }
    
#if _DEBUG
    /// <summary>
    /// 디버그 모드에서는 예외를 발생시켜 실행을 중단합니다.
    /// 릴리스 모드에서는 오류 메시지만 출력하고 계속 실행됩니다.
    /// </summary>
    /// <exception cref="AstrumException">디버그 모드에서만 발생합니다.</exception>
    void Alert() const { throw *this; }
#else
    /// <summary>
    /// 디버그 모드에서는 예외를 발생시켜 실행을 중단합니다.
    /// 릴리스 모드에서는 오류 메시지만 출력하고 계속 실행됩니다.
    /// </summary>
    void Alert() const noexcept { print(); }
#endif
private:
    /// <summary>
    /// 와이드 문자 문자열을 일반 문자열로 변환합니다.
    /// </summary>
    /// <param name="wstr">변환할 와이드 문자 문자열입니다.</param>
    /// <returns>변환된 일반 문자 문자열입니다.</returns>
    std::string wstr2str(const std::wstring& wstr);
    /// <summary>
    /// 예외 메시지를 표준 출력(콘솔)에 출력합니다.
    /// 예외 생성 시 자동으로 호출됩니다.
    /// </summary>
    void print() const noexcept;
};