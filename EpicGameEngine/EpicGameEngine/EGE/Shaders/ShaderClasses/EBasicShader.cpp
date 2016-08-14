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
		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.ByteWidth = sizeof(PointLight);
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Graphics::D3D::FailCheck(Graphics::D3D::gDevice->CreateBuffer(&cbd, 0, &mPointlightBuffer));
	}

	void EBasicShader::CleanUpBuffers()
	{
		Graphics::D3D::ReleaseCom(mPointlightBuffer);
	}

	void EBasicShader::SetPointLight(const PointLight pl)
	{
		
		D3D11_MAPPED_SUBRESOURCE mappedRes;
		ZeroMemory(&mappedRes, sizeof(D3D11_MAPPED_SUBRESOURCE));

		Graphics::D3D::gDeviceContext->Map(mPointlightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		PointLight* dataPtr = (PointLight*)mappedRes.pData;
		*dataPtr = pl;
		Graphics::D3D::gDeviceContext->Unmap(mPointlightBuffer, 0);
		
		Graphics::D3D::gDeviceContext->PSSetConstantBuffers(0, 1, &mPointlightBuffer);
	}
}}