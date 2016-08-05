#include "ICScreen.h"
namespace
{
	EGE::Graphics::ICScreen* gICScreen = 0;
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return gICScreen->MsgProc(hwnd, msg, wParam, lParam);
}


namespace EGE { namespace Graphics{
	namespace D3D
	{
		ID3D11Device*			gDevice;
		IDXGISwapChain*			gSwapChain;
		ID3D11DeviceContext*	gDeviceContext;
		ID3D11RenderTargetView*	gRenderTargetView;
		ID3D11Texture2D*		gDepthStencilBuffer;
		ID3D11DepthStencilView*	gDepthStencilView;
		UINT					gMsaaQuality;
		bool					gEnable4xMsaa;

		bool FailCheck(HRESULT hr)
		{
			if (FAILED(hr))
			{
				MessageBox(0, L"Creation of Context failed", 0, 0);
				return false;
			}
			return true;
		}
	}

	namespace Window
	{
		HINSTANCE	gHInstance;
		HWND		gMainHandle;
		int			gShowCmd, gWidth, gHeight;
		bool		gWindowed;
	}

	ICScreen::ICScreen(int width, int height)
	{
		gICScreen = this;

		EGE::Graphics::Window::gWidth = width;
		EGE::Graphics::Window::gHeight = height;
		EGE::Graphics::Window::gWindowed = true;
		
		EGE::Graphics::D3D::gEnable4xMsaa = true;
	}


	ICScreen::~ICScreen()
	{
	}

	void ICScreen::ICInit()
	{
		WinInit();
		DirectXInit();
	}
	
	void ICScreen::Prepare()
	{

	}

	void ICScreen::Update()
	{
	
	}

	void ICScreen::ICDestroy()
	{
		EGE::Graphics::D3D::gDevice->Release();
		EGE::Graphics::D3D::gDeviceContext->Release();
		EGE::Graphics::D3D::gSwapChain->Release();
		EGE::Graphics::D3D::gRenderTargetView->Release();
		EGE::Graphics::D3D::gDepthStencilBuffer->Release();
		EGE::Graphics::D3D::gDepthStencilView->Release();
	}

	void ICScreen::WinInit()
	{
		WNDCLASS wc;

		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = MainWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = EGE::Graphics::Window::gHInstance;
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

		EGE::Graphics::Window::gMainHandle = CreateWindow(L"Test", L"DirectApp",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			EGE::Graphics::Window::gWidth, EGE::Graphics::Window::gHeight,
			0, 0, EGE::Graphics::Window::gHInstance, 0);

		if (EGE::Graphics::Window::gMainHandle == 0)
		{
			MessageBox(0, L"Creating of window failed", 0, 0);
		}

		ShowWindow(EGE::Graphics::Window::gMainHandle, EGE::Graphics::Window::gShowCmd);
		UpdateWindow(EGE::Graphics::Window::gMainHandle);
	}

	void ICScreen::DirectXInit()
	{
		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featurelvl;
		HRESULT hr = D3D11CreateDevice(
			0,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			createDeviceFlags,
			0, 0,
			D3D11_SDK_VERSION,
			&EGE::Graphics::D3D::gDevice,
			&featurelvl,
			&EGE::Graphics::D3D::gDeviceContext
		);

		if (!EGE::Graphics::D3D::FailCheck(hr))return;
		if (featurelvl != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, L"DirectX11 not supported", 0, 0);
		}

		EGE::Graphics::D3D::gDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &EGE::Graphics::D3D::gMsaaQuality);
		assert(EGE::Graphics::D3D::gMsaaQuality > 0);



		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = EGE::Graphics::Window::gWidth;
		sd.BufferDesc.Height = EGE::Graphics::Window::gHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (EGE::Graphics::D3D::gEnable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = EGE::Graphics::D3D::gMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = EGE::Graphics::D3D::gMsaaQuality - 1;
		}

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = EGE::Graphics::Window::gMainHandle;
		sd.Windowed = EGE::Graphics::Window::gWindowed;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		IDXGIDevice* dxgiDevice = 0;
		EGE::Graphics::D3D::gDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

		IDXGIAdapter* dxgiAdapter = 0;
		dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

		IDXGIFactory* dxgiFactory = 0;
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

		hr = dxgiFactory->CreateSwapChain(EGE::Graphics::D3D::gDevice, &sd, &EGE::Graphics::D3D::gSwapChain);
		//NO ALT-ENTER
		//dxgiFactory->MakeWindowAssociation(EGE::Graphics::Window::gMainHandle, DXGI_MWA_NO_ALT_ENTER);

		dxgiDevice->Release();
		dxgiAdapter->Release();
		dxgiFactory->Release();

		ID3D11Texture2D* backBuffer;
		EGE::Graphics::D3D::gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(&backBuffer));
		EGE::Graphics::D3D::gDevice->CreateRenderTargetView(backBuffer, 0, &EGE::Graphics::D3D::gRenderTargetView);
		backBuffer->Release();

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = EGE::Graphics::Window::gWidth;
		depthStencilDesc.Height = EGE::Graphics::Window::gHeight;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (EGE::Graphics::D3D::gEnable4xMsaa)
		{
			depthStencilDesc.SampleDesc.Count = 4;
			depthStencilDesc.SampleDesc.Quality = EGE::Graphics::D3D::gMsaaQuality - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = EGE::Graphics::D3D::gMsaaQuality - 0;
		}
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		EGE::Graphics::D3D::gDevice->CreateTexture2D(&depthStencilDesc,
			0,
			&EGE::Graphics::D3D::gDepthStencilBuffer);

		EGE::Graphics::D3D::gDevice->CreateDepthStencilView(EGE::Graphics::D3D::gDepthStencilBuffer,
			0,
			&EGE::Graphics::D3D::gDepthStencilView);

		EGE::Graphics::D3D::gDeviceContext->OMSetRenderTargets(1, &EGE::Graphics::D3D::gRenderTargetView, EGE::Graphics::D3D::gDepthStencilView);

		D3D11_VIEWPORT vp;
		vp.TopLeftX = 0.f;
		vp.TopLeftY = 0.f;
		vp.Width = static_cast<float>(EGE::Graphics::Window::gWidth);
		vp.Height = static_cast<float>(EGE::Graphics::Window::gHeight);
		vp.MinDepth = 0.f;
		vp.MaxDepth = 0.f;

		EGE::Graphics::D3D::gDeviceContext->RSSetViewports(1, &vp);
	}


	LRESULT ICScreen::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}}