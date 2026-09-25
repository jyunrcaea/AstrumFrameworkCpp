#include <windows.h>
#include <iostream>
#include <string_view>

// 예제 파일들은 각각 독립된 네임스페이스에 Program::Main()을 정의합니다.
// 이 파일에서 한번에 포함해 컴파일하므로, 예제 .cpp 파일들은 개별적으로 컴파일하지 않습니다.
#include "LifeCycle.cpp"
#include "DependencyInjection.cpp"
#include "RectMoving.cpp"

// 사용법: AstrumExamples.exe [RectMoving | LifeCycle | DependencyInjection]
// 인자가 없으면 RectMoving 예제를 실행합니다.
int main(int argc, char* argv[]) {
    const std::string_view name = argc > 1 ? argv[1] : "RectMoving";

    // WIC로 이미지를 불러오기 위해 COM 초기화가 필요합니다.
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED))) {
        std::cerr << "CoInitializeEx failed." << std::endl;
        return 1;
    }

    int result = 0;
    if (name == "RectMoving") result = RectMoving::Program::Main();
    else if (name == "LifeCycle") result = LifeCycle::Program::Main();
    else if (name == "DependencyInjection") result = DependencyInjection::Program::Main();
    else {
        std::cerr << "Unknown example: " << name << "\n"
            << "Usage: AstrumExamples.exe [RectMoving | LifeCycle | DependencyInjection]" << std::endl;
        result = 1;
    }

    CoUninitialize();
    return result;
}
