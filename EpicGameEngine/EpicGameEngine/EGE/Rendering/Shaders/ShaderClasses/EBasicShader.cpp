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

		mCamPositionPix = std::make_unique<ConstantBuffer>();
		mCamPositionPix->InitBuffer(sizeof(CamPos), SHADERKINDS::PixelShader);

		mCamPositionVer = std::make_unique<ConstantBuffer>();
		mCamPositionVer->InitBuffer(sizeof(CamPos), SHADERKINDS::VertexShader);

		DirectX::XMMATRIX a = DirectX::XMMatrixPerspectiveFovLH(0.25f * 3.1415f, Graphics::Window::AspectRatio(), 1.0f, 100.f);
		//DirectX::XMMATRIX a = DirectX::XMMatrixIdentity();
		mCBufferPerInstance->UpdateBuffer(&a);
		mCBufferPerInstance->SetActiveBuffer(0);

		Vec2f pos = { 0.0f, 0.0f };
		mCamPositionPix->UpdateBuffer(&pos);
		mCamPositionPix->SetActiveBuffer(1);

		mCamPositionVer->UpdateBuffer(&pos);
		mCamPositionVer->SetActiveBuffer(1);
	}

	void EBasicShader::CleanUpBuffers()
	{
	}

	void EBasicShader::SetPointLight(PointLight pl)
	{
		mPointLightBuffer->UpdateBuffer(&pl);
		mPointLightBuffer->SetActiveBuffer(0);
	}

	void EBasicShader::UpdatePointLight()
	{
	}

	
	void EBasicShader::SetCamPos(Vec2f pos)
	{
		CamPos p;
		p.pos = pos;
		p.padding = { 0, 0 };
		mCamPositionPix->UpdateBuffer(&p);
		mCamPositionPix->SetActiveBuffer(1);


		mCamPositionVer->UpdateBuffer(&p);
		mCamPositionVer->SetActiveBuffer(1);
	}
}}