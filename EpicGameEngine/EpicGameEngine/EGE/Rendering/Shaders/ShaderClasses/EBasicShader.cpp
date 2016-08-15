#include "EBasicShader.h"

namespace EGE { namespace Shaders{
	void EBasicShader::CreateInputLayout(std::vector<uint8_t> vertexShaderBuffer)
	{
		D3D11_INPUT_ELEMENT_DESC elementDesc[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Colour", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		constexpr unsigned int NUMARGS{ 2 };

		Graphics::D3D::FailCheck(Graphics::D3D::gDevice->CreateInputLayout(elementDesc, NUMARGS, vertexShaderBuffer.data(), vertexShaderBuffer.size(), &mInputLayout));
	}

	void EBasicShader::InitializeCBuffers()
	{
		mPointLightBuffer = std::make_unique<ConstantBuffer>();
		mPointLightBuffer->InitBuffer(sizeof(PointLightBuffer), SHADERKINDS::PixelShader);

		mCBufferPerInstance = std::make_unique<ConstantBuffer>();
		mCBufferPerInstance->InitBuffer(sizeof(CBufferPerInstance), SHADERKINDS::VertexShader);

		DirectX::XMMATRIX a = DirectX::XMMatrixPerspectiveFovLH(0.25f * 3.1415f, Graphics::Window::AspectRatio(), 1.0f, 100.f);
		//DirectX::XMMATRIX a = DirectX::XMMatrixIdentity();
		mCBufferPerInstance->UpdateBuffer(&a);
		mCBufferPerInstance->SetActiveBuffer(0);
	}

	void EBasicShader::CleanUpBuffers()
	{
	}

	void EBasicShader::SetPointLight(PointLight pl)
	{
		mPointLightBuffer->UpdateBuffer(&pl);
		mPointLightBuffer->SetActiveBuffer(0);
	}
}}