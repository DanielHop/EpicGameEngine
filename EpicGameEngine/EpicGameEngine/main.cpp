#include <windows.h>

#include "EGE\Instances\TestInstance.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd)
{
	TestInstance test(hInstance, nShowCmd);
	test.Run();

}
