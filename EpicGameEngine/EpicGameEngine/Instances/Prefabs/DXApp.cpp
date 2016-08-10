#include "DXApp.h"

DXApp::DXApp(const HINSTANCE hInstance, const int nShowCmd)
{

	Window::gHInstance = hInstance;
	Window::gShowCmd = nShowCmd;
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
			Update(0.0f);
			Render();
			screen->Update();
		}
	}

	Destroy();
	screen->Destroy();
}