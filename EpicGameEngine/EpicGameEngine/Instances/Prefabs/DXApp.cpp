#include "DXApp.h"

DXApp::DXApp(const HINSTANCE hInstance, const int nShowCmd)
{

	Window::gHInstance = hInstance;
	Window::gShowCmd = nShowCmd;

	mScreen = std::make_unique<EScreen>();
	mGameTimer = std::make_unique<GameTimer>();
}

void DXApp::Run()
{
	mScreen->Init();
	InitMessageloop();
	Init();
	
	mGameState = GameState::INGAME;

	auto dt = 0.f;
	auto msg = MSG{ 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			mGameTimer->Tick();
			if (mGameState == GameState::INGAME)
			{
				dt += mGameTimer->DeltaTime();
				if(dt >= 1.f / TICKSPERSECOND)
				{
					Update(mGameTimer->DeltaTime() / (1.f / TICKSPERSECOND));
					dt = 0;
				}
			}
			mScreen->Prepare();
			Render();
			mScreen->Update();
		}
	}

	Destroy();
	mScreen->Destroy();
}

void DXApp::InitMessageloop()
{
	mScreen->SetMessageloopFunction([this](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case 0x41:
				KeyDown("A");
				break;
			case 0x44:
				KeyDown("D");
				break;
			case 0x50:
				KeyDown("P");
				break;
			case 0x51:
				KeyDown("Q");
				break;
			case 0x52:
				KeyDown("R");
				break;
			case 0x53:
				KeyDown("S");
				break;
			case 0x57:
				KeyDown("W");
				break;
			}
			break;
		case WM_KEYUP:
			switch (wParam)
			{
			case 0x41:
				KeyUp("A");
				break;
			case 0x44:
				KeyUp("D");
				break;
			case 0x57:
				KeyUp("W");
				break;
			case 0x53:
				KeyUp("S");
				break;
			}
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	});
}