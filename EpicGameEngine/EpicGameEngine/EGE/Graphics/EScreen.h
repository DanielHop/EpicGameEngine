#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <cassert>

#include "../Content/IContent.h"

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

		bool FailCheck(HRESULT hr);
	}

	namespace Window
	{
		extern HINSTANCE	gHInstance;
		extern HWND			gMainHandle;
		extern int			gShowCmd, gWidth, gHeight;
		extern bool			gWindowed;
	}
	class EScreen : public EGE::Content::IContent
	{
	public:
		EScreen(int width, int height);
		~EScreen();
		
		void Prepare();
		void Update();


		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:
		virtual void ICInit()override;
		virtual void ICDestroy()override;
	private:
		void WinInit();
		void DirectXInit();

	private:
		int mWidth, mHeight;
	};
}}
