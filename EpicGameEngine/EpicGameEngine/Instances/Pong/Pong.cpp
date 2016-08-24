#include "Pong.h"



Pong::Pong(const HINSTANCE hInstance, const int nShowCmd)
	:DXApp{ hInstance, nShowCmd }
{
	mRenderer = std::make_unique<EBasicRenderer>();
	thePlayer = std::make_unique<Player>();
	EGE::Graphics::Window::gWidth = 780;
	EGE::Graphics::Window::gHeight = 585;
}


Pong::~Pong()
{
}


void Pong::Init()
{
	mRenderer->Init();
	thePlayer->Init();

	p.range = 2.f;
	p.pos = Vec2f{ 0.f, 0.f };
	p.colour = Vec3f{ 1.0f, 1.0f, 1.0f };
	p.padding = { 0,0 };

	//mRenderer->SetPointLight(p);

	sprites.push_back(thePlayer->GetSprite());
}

void Pong::Keydown(std::string key)
{
	if (key == "W")
		thePlayer->MoveUp();
	if (key == "S")
		thePlayer->MoveDown();
}

void Pong::Update(const Timestep dt)
{
	if (mGameState == GameState::INGAME)
	{

	sprites[0] = thePlayer->GetSprite();
	}
}

void Pong::Render()
{
	mRenderer->Prepare(sprites);
	auto changeBuf = (mLastRenderer == RENDERERS::EBasicRenderers) ? false : true;
	mRenderer->Render(changeBuf);
	mLastRenderer = RENDERERS::EBasicRenderers;

}
void Pong::Destroy()
{
	mRenderer->Destroy();
}