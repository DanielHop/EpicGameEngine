#include "EBasicRenderer.h"

namespace EGE { namespace Rendering {
	void EBasicRenderer::SetPointLight(const Shaders::PointLight pl)const
	{
		mShader->SetPointLight(pl);
	}
	
	void EBasicRenderer::InitializeShader()
	{
		mShader->Init();
		mShader->SetActive();
	}

	void EBasicRenderer::InitializeBuffers()
	{
		InitializeDynamicVertexBuffer(sizeof(Vertex) * VERTICESPERSPRITE * MAXNUMSPRITES);
		
		InitializeIndexBuffer();
	}

	void EBasicRenderer::Begin()
	{
		mNumOfSprites = 0;

		D3D11_MAPPED_SUBRESOURCE mappedRes;
		ZeroMemory(&mappedRes, sizeof(D3D11_MAPPED_SUBRESOURCE));

		Graphics::D3D::gDeviceContext->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		dataPtr = (Vertex*) mappedRes.pData;

		mShader->SetCamPos(mCameraPos);
	}

	void EBasicRenderer::AddToStack(const Models::Sprite sprite)
	{
		Math::Vec4f colour = sprite.colour;
		
		//ABOVE LEFT
		*dataPtr = { sprite.pos, colour };
		dataPtr++;

		//ABOVE RIGHT
		*dataPtr = { { sprite.pos.x + sprite.size.x,  sprite.pos.y, sprite.pos.z} ,colour };
		dataPtr++;

		//DOWN RIGHT
		*dataPtr = { { sprite.pos.x + sprite.size.x,  sprite.pos.y - sprite.size.y, sprite.pos.z },colour };
		dataPtr++;

		//DOWN LEFT
		*dataPtr = { { sprite.pos.x ,  sprite.pos.y - sprite.size.y, sprite.pos.z }, colour };
		dataPtr++;

		//Increase number of sprites
		mNumOfSprites++;
	}

	void EBasicRenderer::End()
	{
		Graphics::D3D::gDeviceContext->Unmap(mVertexBuffer, 0);
	}

	void EBasicRenderer::Flush(const bool shouldSetBuffers)const
	{
		auto stride = sizeof(Vertex);
		auto offset = static_cast<UINT>(0);
		if(shouldSetBuffers)
		{
			Graphics::D3D::gDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
			Graphics::D3D::gDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
			mShader->SetActive();
		}
		Graphics::D3D::gDeviceContext->DrawIndexed(6 * mNumOfSprites, 0, 0);
	}

	void EBasicRenderer::DeleteShader()
	{
		mShader->Destroy();
	}

	void EBasicRenderer::InitializeIndexBuffer()
	{

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_IMMUTABLE;
		bd.ByteWidth = sizeof(unsigned int) * 6 * MAXNUMSPRITES;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		std::vector<unsigned int> array;
		for (int i = 0; i < MAXNUMSPRITES; i++)
		{
			array.push_back(0 + i * 4);
			array.push_back(1 + i * 4);
			array.push_back(2 + i * 4);
			array.push_back(0 + i * 4);
			array.push_back(2 + i * 4);
			array.push_back(3 + i * 4);
		}

		D3D11_SUBRESOURCE_DATA sb;
		ZeroMemory(&sb, sizeof(sb));
		sb.pSysMem = array.data();

		Graphics::D3D::gDevice->CreateBuffer(&bd, &sb, &mIndexBuffer);
	}
}}