#include <windows.h>

#include "Instances/Pong/Pong.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd)
{
	Pong test(hInstance, nShowCmd);
	test.Run();
}