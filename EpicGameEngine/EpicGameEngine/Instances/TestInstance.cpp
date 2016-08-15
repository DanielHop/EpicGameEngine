#include "TestInstance.h"



TestInstance::TestInstance(const HINSTANCE hInstance, const int nShowCmd)
	:DXApp{ hInstance, nShowCmd }
{
}


TestInstance::~TestInstance()
{
}


void TestInstance::Init()
{
	std::cout << "hi";

	mRenderer->Init();

	sprites.push_back({ {-0.5f, 0.5f}, {1.0f, 1.0f}, { 1, 0.f, 0.f, 1.f}, { 0 } });

	p.range = 2.f;
	p.pos = Vec2f{ 0.f, 0.f };
	p.colour = Vec3f{ 1.0f, 1.0f, 1.0f };
	p.padding = { 0,0 };

	mRenderer->SetPointLight(p);
}

void TestInstance::Keydown(std::string key)
{
	if(key == "W")
		p.pos = { p.pos.x , p.pos.y + 0.01f };
	if(key == "S")
		p.pos = { p.pos.x , p.pos.y - 0.01f };
	mRenderer->SetPointLight(p);
}

void TestInstance::Update(const Timestep dt)
{

}

void TestInstance::Render()
{
	mRenderer->Prepare(sprites);
	auto changeBuf = (mLastRenderer == RENDERERS::EBasicRenderers) ? false : true;
	mRenderer->Render(changeBuf);
	mLastRenderer = RENDERERS::EBasicRenderers;

}
void TestInstance::Destroy()
{
	mRenderer->Destroy();
}