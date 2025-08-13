#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#endif

//#include "Tests/RectMoving.hpp"
#include "Tests/NoteTest.hpp"

int main()
{
#ifdef _DEBUG
	SetConsoleTitleA("Astrum Framework Test");
	std::cin.tie(0)->sync_with_stdio(false);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    try {
        Program().Main();
    } catch (const AstrumException& e) {
        std::cerr << "Astrum Exception: " << e.what() << std::endl;
        throw e;
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    return main();
} 