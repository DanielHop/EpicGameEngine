#include "IRenderer.h"

namespace EGE { namespace Rendering {

	void IRenderer::Prepare(const std::vector<Models::Sprite> spritesToRender)
	{
		Begin();
		for (auto s : spritesToRender)
			AddToStack(s);
		End();
	}

	void IRenderer::Render(const bool shouldSetBuffers)const
	{
		Flush(shouldSetBuffers);
	}

	void IRenderer::InitializeDynamicVertexBuffer(const unsigned int byteWidth)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;               
		bd.ByteWidth = byteWidth;						
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;      
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    

		Graphics::D3D::gDevice->CreateBuffer(&bd, nullptr, &mVertexBuffer);
	}

	void IRenderer::Init()
	{
		InitializeBuffers();
		InitializeShader();
	}

	void IRenderer::Destroy()
	{
		Graphics::D3D::ReleaseCom(mVertexBuffer);
		Graphics::D3D::ReleaseCom(mIndexBuffer);
		DeleteShader();
	}
}}