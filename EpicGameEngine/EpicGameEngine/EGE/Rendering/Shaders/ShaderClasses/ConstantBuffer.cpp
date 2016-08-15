#include "ConstantBuffer.h"

namespace EGE { namespace Shaders{

	void ConstantBuffer::InitBuffer(const UINT size, SHADERKINDS kind)
	{
		this->mSize = size;
		this->mKind = kind;

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.ByteWidth = size;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Graphics::D3D::FailCheck(Graphics::D3D::gDevice->CreateBuffer(&cbd, 0, &mCBuffer));
	}

	void ConstantBuffer::UpdateBuffer(void* data)
	{
		D3D11_MAPPED_SUBRESOURCE mappedRes;
		ZeroMemory(&mappedRes, sizeof(D3D11_MAPPED_SUBRESOURCE));

		auto hr = Graphics::D3D::gDeviceContext->Map(mCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		auto ptr = (BBuffer*)mappedRes.pData;
		auto dataptr = (BBuffer*)data;
		*ptr = *dataptr;
		Graphics::D3D::gDeviceContext->Unmap(mCBuffer, 0);
	}

	void ConstantBuffer::SetActiveBuffer(const UINT slot)const
	{
		if (mKind == SHADERKINDS::VertexShader)
			Graphics::D3D::gDeviceContext->VSSetConstantBuffers(slot, 1, &mCBuffer);
		if (mKind == SHADERKINDS::PixelShader)
			Graphics::D3D::gDeviceContext->PSSetConstantBuffers(slot, 1, &mCBuffer);
	}
}}