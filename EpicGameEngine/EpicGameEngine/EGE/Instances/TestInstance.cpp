#include "TestInstance.h"



TestInstance::TestInstance(HINSTANCE hInstance, int nShowCmd)
	:DXApp(hInstance, nShowCmd)
{
}


TestInstance::~TestInstance()
{
}


void TestInstance::Init()
{
	auto vsb = EGE::Util::BasicReader::ReadData("C:\Programming\CPP\EpicGameEngine\EpicGameEngine\Debug\BasicVertexShader.cso");
	auto psb = EGE::Util::BasicReader::ReadData("C:\Programming\CPP\EpicGameEngine\EpicGameEngine\Debug\BasicPixelShader.cso");
	EGE::Graphics::D3D::FailCheck(EGE::Graphics::D3D::gDevice->CreateVertexShader(&(vsb.at(0)), vsb.size(), NULL, (mVs.GetPointerInstance())));
	EGE::Graphics::D3D::FailCheck(EGE::Graphics::D3D::gDevice->CreatePixelShader(&(psb.at(0)), psb.size(), NULL, (mPs.GetPointerInstance())));
}

void TestInstance::Destroy()
{
}