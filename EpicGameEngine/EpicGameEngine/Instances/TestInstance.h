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

	void Keydown(std::string key)override;
private:
	std::unique_ptr<EBasicRenderer> mRenderer{ new EBasicRenderer() };

	std::vector<Sprite> sprites;
	RENDERERS mLastRenderer{ RENDERERS::null };
	SHADERS mLastShader{ SHADERS::null };

	PointLight p;
};

