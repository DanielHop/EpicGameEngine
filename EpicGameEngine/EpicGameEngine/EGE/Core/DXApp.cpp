#include "DXApp.h"

DXApp::DXApp(HINSTANCE hInstance, int nShowCmd)
{

	EGE::Graphics::Window::gHInstance = hInstance;
	EGE::Graphics::Window::gShowCmd = nShowCmd;
}

void DXApp::Run()
{
	screen->Init();
	Init();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			screen->Prepare();
			screen->Update();
		}
	}

	Destroy();
	screen->Destroy();
}