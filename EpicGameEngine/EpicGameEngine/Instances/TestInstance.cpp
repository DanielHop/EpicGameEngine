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

//	sprites.push_back({ {-0.5f, 0.5f}, {1.0f, 1.0f}, { 1, 0.f, 0.f, 1.f}, { 0.25 * 3.1415f } });

	auto nSprites = 200;
	auto length = 2.0f / (float)nSprites;
	for (auto y = 0; y < nSprites; y++)
	{
		for (auto x = 0; x < nSprites; x++)
		{
			sprites.push_back({ { (float)x / (float)nSprites * 2 - 1.f, (float)y / (float)nSprites * 2 - 1.f },{ length , length },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0.25 * 3.1415f } });

		}
	}

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