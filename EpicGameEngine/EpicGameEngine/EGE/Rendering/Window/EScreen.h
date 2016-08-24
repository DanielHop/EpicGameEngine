#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <directXMath.h>
#include <cassert>
#include <string>
#include <atlcore.h>
#include <functional>

using MessageloopFunction = std::function<LRESULT (HWND, UINT, WPARAM, LPARAM)>;

namespace EGE { namespace Graphics{
	namespace D3D
	{
		extern ID3D11Device*			gDevice;
		extern IDXGISwapChain*			gSwapChain;
		extern ID3D11DeviceContext*		gDeviceContext;
		extern ID3D11RenderTargetView*	gRenderTargetView;
		extern ID3D11Texture2D*			gDepthStencilBuffer;
		extern ID3D11DepthStencilView*	gDepthStencilView;
		extern UINT						gMsaaQuality;
		extern bool						gEnable4xMsaa;

		bool FailCheck(const HRESULT hr, const std::string text = "SOMETHING WENT WRONG NO DEFAULT TEXT SPECIFIED");
		void ReleaseCom(IUnknown* comptr);
		
	}

	namespace Window
	{
		extern HINSTANCE	gHInstance;
		extern HWND			gMainHandle;
		extern int			gShowCmd;
		//extern int gWidth{ 780 }, gHeight{ 585 };
		extern int gWidth;
		extern int gHeight;
		extern bool			gWindowed;
		float AspectRatio();
	}

	class EScreen
	{
	public:		
		void Prepare()const;
		void Update()const;

		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		~EScreen() {}

		void Init();
		void Destroy();

		void SetMessageloopFunction(MessageloopFunction mlf) { this->mlf = mlf; }
	private:
		void WinInit() const;
		void DirectXInit() const;

	private:
		MessageloopFunction mlf{ [] (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
		{ 
			switch (msg)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			} 
			return DefWindowProc(hwnd, msg, wParam, lParam); 
		} };
	};
}}
