#include "EScreen.h"

namespace
{
	EGE::Graphics::EScreen* gEScreenMainWndProc = 0;
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return gEScreenMainWndProc->MsgProc(hwnd, msg, wParam, lParam);
}



namespace EGE { namespace Graphics{
	namespace D3D
	{
		ID3D11Device*			gDevice;
		IDXGISwapChain*			gSwapChain;
		ID3D11DeviceContext*		gDeviceContext;
		ID3D11RenderTargetView*	gRenderTargetView;
		ID3D11Texture2D*			gDepthStencilBuffer;
		ID3D11DepthStencilView*	gDepthStencilView;
		UINT					gMsaaQuality;
		bool					gEnable4xMsaa;

		bool FailCheck(const HRESULT hr, const std::string text)
		{
			if (FAILED(hr))
			{
				MessageBox(0, LPCWSTR(text.c_str()), 0, 0);
				return false;
			}
			return true;
		}

		void ReleaseCom(IUnknown* comptr)
		{
			comptr->Release();
		//	comptr = nullptr;
		}
	}

	namespace Window
	{
		HINSTANCE	gHInstance;
		HWND		gMainHandle;
		int			gShowCmd;
		bool		gWindowed;

		float AspectRatio()
		{
			return (float)gWidth / (float)gHeight;
		}
	}

	void EScreen::Init()
	{

		gEScreenMainWndProc = this;
		EGE::Graphics::Window::gWindowed = true;
		EGE::Graphics::D3D::gEnable4xMsaa = true;
		WinInit();
		DirectXInit();
	}
	
	void EScreen::Prepare()const
	{
		DirectX::XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
		D3D::gDeviceContext->ClearRenderTargetView(D3D::gRenderTargetView, reinterpret_cast<const float*>(&Black));
		D3D::gDeviceContext->ClearDepthStencilView(D3D::gDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		D3D::gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void EScreen::Update()const
	{
		D3D::gSwapChain->Present(0, 0);
	}

	void EScreen::Destroy()
	{
		D3D::ReleaseCom(D3D::gDevice);
		D3D::ReleaseCom(D3D::gSwapChain);
		D3D::ReleaseCom(D3D::gDeviceContext);
		D3D::ReleaseCom(D3D::gRenderTargetView);
		D3D::ReleaseCom(D3D::gDepthStencilBuffer);
		D3D::ReleaseCom(D3D::gDepthStencilView);
	}					

	void EScreen::WinInit() const
	{
		WNDCLASS wc;

		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = MainWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = Window::gHInstance;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = 0;
		wc.lpszClassName = L"Test";

		if (!RegisterClass(&wc))
		{
			MessageBox(0, L"Register class failed", 0, 0);
			return;
		}

		Window::gMainHandle = CreateWindow(L"Test", L"DirectApp",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			Window::gWidth, Window::gHeight,
			0, 0, Window::gHInstance, 0);

		if (Window::gMainHandle == 0)
		{
			MessageBox(0, L"Creating of window failed", 0, 0);
			return;
		}
		else 
		{
			ShowWindow(Window::gMainHandle, Window::gShowCmd);
			UpdateWindow(Window::gMainHandle);
		}
	}

	void EScreen::DirectXInit() const
	{
		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featurelvl;
		if (!D3D::FailCheck(D3D11CreateDevice(
			0,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			createDeviceFlags,
			0, 0,
			D3D11_SDK_VERSION,
			&D3D::gDevice,
			&featurelvl,
			&D3D::gDeviceContext)))
				return;
		if (featurelvl != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, L"DirectX11 not supported", 0, 0);
			return;
		}

		D3D::gDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &D3D::gMsaaQuality);
		assert(D3D::gMsaaQuality > 0);

				DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = Window::gWidth;
		sd.BufferDesc.Height = Window::gHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (D3D::gEnable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = D3D::gMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = D3D::gMsaaQuality - 1;
		}

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = Window::gMainHandle;
		sd.Windowed = Window::gWindowed;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		IDXGIDevice* dxgiDevice = 0;
		D3D::gDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

		IDXGIAdapter* dxgiAdapter = 0;
		dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

		IDXGIFactory* dxgiFactory = 0;
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

		D3D::FailCheck(dxgiFactory->CreateSwapChain(D3D::gDevice, &sd, &D3D::gSwapChain));
		//NO ALT-ENTER
		//dxgiFactory->MakeWindowAssociation(Window::gMainHandle, DXGI_MWA_NO_ALT_ENTER);

		dxgiDevice->Release();
		dxgiAdapter->Release();
		dxgiFactory->Release();

		ID3D11Texture2D* backBuffer;
		D3D::gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(&backBuffer));
		D3D::gDevice->CreateRenderTargetView(backBuffer, 0, &D3D::gRenderTargetView);
		backBuffer->Release();

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = Window::gWidth;
		depthStencilDesc.Height = Window::gHeight;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (D3D::gEnable4xMsaa)
		{
			depthStencilDesc.SampleDesc.Count = 4;
			depthStencilDesc.SampleDesc.Quality = D3D::gMsaaQuality - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = D3D::gMsaaQuality - 0;
		}
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		D3D::FailCheck(D3D::gDevice->CreateTexture2D(&depthStencilDesc,
			0,
			&D3D::gDepthStencilBuffer));

		D3D::FailCheck(D3D::gDevice->CreateDepthStencilView(D3D::gDepthStencilBuffer,
			0,
			&D3D::gDepthStencilView));

		D3D::gDeviceContext->OMSetRenderTargets(1, &D3D::gRenderTargetView, D3D::gDepthStencilView);

		D3D11_VIEWPORT vp;
		vp.TopLeftX = 0.f;
		vp.TopLeftY = 0.f;
		vp.Width = static_cast<float>(Window::gWidth);
		vp.Height = static_cast<float>(Window::gHeight);
		vp.MinDepth = 0.f;
		vp.MaxDepth = 0.f;

		D3D::gDeviceContext->RSSetViewports(1, &vp);
	}


	LRESULT EScreen::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return mlf(hwnd, msg, wParam, lParam);
	}
}}