#include "AstrumException.hpp"
#include <iostream>
#include <windows.h>

std::string AstrumException::wstr2str(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();

    // 필요한 버퍼 크기 계산
    int size_needed = WideCharToMultiByte(
        CP_UTF8,                 // 변환할 코드페이지 (UTF-8 권장)
        0,                       // 변환 옵션
        wstr.c_str(),            // 입력 문자열
        (int)wstr.size(),        // 입력 길이
        nullptr, 0,              // 출력 버퍼 없음 (크기 계산만)
        nullptr, nullptr         // 기본 문자 (필요 없으면 nullptr)
    );

    std::string str(size_needed, 0);

    WideCharToMultiByte(
        CP_UTF8,
        0,
        wstr.c_str(),
        (int)wstr.size(),
        &str[0], size_needed,
        nullptr, nullptr
    );

    return str;
}

void AstrumException::print() {
    std::cout << "[AstrumException]" << this->what() << std::endl;
}