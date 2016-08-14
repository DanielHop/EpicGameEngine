#include "DXApp.h"

DXApp::DXApp(const HINSTANCE hInstance, const int nShowCmd)
{

	Window::gHInstance = hInstance;
	Window::gShowCmd = nShowCmd;
}

void DXApp::Run()
{
	screen->Init();
	InitMessageloop();
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

void DXApp::InitMessageloop()
{
	screen->SetMessageloopFunction([this](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
		case WM_KEYDOWN:
			if (wParam == 0x57)
				Keydown("W");
			if (wParam == 0x53)
				Keydown("S");
			return 0;

		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	});
}