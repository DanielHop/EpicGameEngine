#include "TestInstance.h"



TestInstance::TestInstance(const HINSTANCE hInstance, const int nShowCmd)
	:DXApp{ hInstance, nShowCmd }
{
}


TestInstance::~TestInstance()
{
	D3D::ReleaseCom(pVBuffer);
}


void TestInstance::Init()
{
	mShader->Init();
	mShader->SetActive();
	Vertex OurVertices[] =
	{
		{ 0.0f, 0.5f, 0.0f },
		{ 0.45f, -0.5, 0.0f },
		{ -0.45f, -0.5f, 0.0f }
	};

	   // global

	D3D11_SUBRESOURCE_DATA sr;
	sr.pSysMem = OurVertices;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_IMMUTABLE;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(Vertex) * 3;             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = 0;    // allow CPU to write in buffer

	D3D::gDevice->CreateBuffer(&bd, &sr, &pVBuffer);
}

void TestInstance::Update(const Timestep dt)
{

}

void TestInstance::Render()
{
	auto stride = sizeof(Vertex);
	auto offset = static_cast<UINT>(0);
	D3D::gDeviceContext->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	D3D::gDeviceContext->Draw(3, 0);
}
void TestInstance::Destroy()
{
}