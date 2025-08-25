#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#endif

//#include "Game/RectMoving.hpp"
#include "Game/NoteTest.hpp"
//#include "Game/FrameworkTest.hpp"

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
    Program::Main();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    return main();
}