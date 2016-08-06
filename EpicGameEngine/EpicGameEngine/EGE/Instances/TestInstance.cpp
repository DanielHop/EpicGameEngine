#include "TestInstance.h"



TestInstance::TestInstance(HINSTANCE hInstance, int nShowCmd)
	:DXApp{ hInstance, nShowCmd }
{
}


TestInstance::~TestInstance()
{
}


void TestInstance::Init()
{
	auto vsb = EGE::Util::BasicReader::ReadData("C:/Programming/CPP/EpicGameEngine/EpicGameEngine/Debug/BasicVertexShader.cso");
	auto psb = EGE::Util::BasicReader::ReadData("C:/Programming/CPP/EpicGameEngine/EpicGameEngine/Debug/BasicPixelShader.cso");

	D3D::FailCheck(D3D::gDevice->CreateVertexShader(&(vsb.at(0)), vsb.size(), NULL, mVs.GetPointerInstance()));
	D3D::FailCheck(D3D::gDevice->CreatePixelShader(&(psb.at(0)), psb.size(), NULL, mPs.GetPointerInstance()));
	D3D::gDeviceContext->PSSetShader(mPs.GetInstance(), NULL, NULL);
	D3D::gDeviceContext->VSSetShader(mVs.GetInstance(), NULL, NULL);
	
	D3D11_INPUT_ELEMENT_DESC elementDesc[]
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	ID3D11InputLayout* layout;
	D3D::FailCheck(D3D::gDevice->CreateInputLayout(elementDesc, 1, &(vsb.at(0)), vsb.size(), &layout));

	D3D::gDeviceContext->IASetInputLayout(layout);
	layout->Release();

}
void TestInstance::Destroy()
{
}