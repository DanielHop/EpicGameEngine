#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <directXMath.h>
#include <cassert>
#include <string>

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

		bool FailCheck(const HRESULT hr, const std::string text = "SOMETHING WENT WRONG NO DEFAULT TEXT SPECIFIED");
		void ReleaseCom(IUnknown* comptr);
	}

	namespace Window
	{
		extern HINSTANCE	gHInstance;
		extern HWND			gMainHandle;
		extern int			gShowCmd;
		constexpr int gWidth{ 1280 }, gHeight{ 720 };
		extern bool			gWindowed;
	}

	class EScreen : public EGE::Content::IContent
	{
	public:		
		void Prepare()const;
		void Update()const;

		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:
		virtual void IInit()override;
		virtual void IDestroy()override;
	private:
		void WinInit() const;
		void DirectXInit() const;
	};
}}
