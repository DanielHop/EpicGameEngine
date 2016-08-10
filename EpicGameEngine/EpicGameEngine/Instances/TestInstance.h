#pragma once

#include "Prefabs/DXApp.h"

struct Vertex
{
	float x, y, z;
};

class TestInstance : public DXApp
{
public:
	TestInstance(const HINSTANCE hInstance, const int nShowCmd);
	~TestInstance();

	void Init() override;
	void Destroy()override;

protected:
	void Update(const Timestep dt)override;
	void Render()override;
private:
	ID3D11Buffer*					pVBuffer{ nullptr };
	std::unique_ptr<ETestShader>	mShader{ new ETestShader() };
};

