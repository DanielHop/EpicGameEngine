#pragma once

#include "../Core/DXApp.h"
#include "../Util/EGEUtil.h"

using namespace EGE::Util;

class TestInstance : public DXApp
{
public:
	TestInstance(HINSTANCE hInstance, int nShowCmd);
	~TestInstance();

	void Init() override;
	void Destroy()override;

private:
	Comptr<ID3D11VertexShader> mVs;
	Comptr<ID3D11PixelShader> mPs;
};

