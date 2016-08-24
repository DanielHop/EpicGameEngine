#include "Pong.h"



Pong::Pong(const HINSTANCE hInstance, const int nShowCmd)
	:DXApp{ hInstance, nShowCmd }
{
	mRenderer = std::make_unique<EBasicRenderer>();
	EGE::Graphics::Window::gWidth = 780;
	EGE::Graphics::Window::gHeight = 585;
	
	thePlayer = std::make_unique<Player>();
	theEnemy = std::make_unique<Enemy>();
	theBall = std::make_unique<Ball>();

}


Pong::~Pong()
{
}


void Pong::Init()
{
	mRenderer->Init();
	thePlayer->Init();
	theEnemy->Init();
	theBall->Init();

	p.range = 2.f;
	p.pos = Vec2f{ 0.f, 0.f };
	p.colour = Vec3f{ 1.0f, 1.0f, 1.0f };
	p.padding = { 0,0 };

	//mRenderer->SetPointLight(p);

	sprites.push_back(thePlayer->GetPaddle().GetSprite());
	sprites.push_back(theEnemy->GetPaddle().GetSprite());
	sprites.push_back(theBall->GetSprite());
}


void Pong::Update(const Timestep dt)
{
	if (mGameState == GameState::INGAME)
	{
		thePlayer->Update(dt);
		theEnemy->Update(dt, theBall->GetSprite().pos.y);
		theBall->Update(dt);

		CollisionCheck();

		PrepareSprites();
	}
}

void Pong::CollisionCheck()
{
	auto ballPos = theBall->GetSprite().pos;
	if (ballPos.x + theBall->GetSprite().size.x >= thePlayer->GetPaddle().GetSprite().pos.x)
	{
		if(ballPos.y >= thePlayer->GetPaddle().GetSprite().pos.y - thePlayer->GetPaddle().GetSprite().size.y && ballPos.y - theBall->GetSprite().size.y <= thePlayer->GetPaddle().GetSprite().pos.y)
			theBall->FlipVel({ -1.0f, 1.0f });
		else
		{
			enemyPoints++;
			ResetLevel();
			mGameState = GameState::PAUSE;
		}
	}
	else if (ballPos.x <= theEnemy->GetPaddle().GetSprite().pos.x + theEnemy->GetPaddle().GetSprite().size.x)
	{
		if (ballPos.y >= theEnemy->GetPaddle().GetSprite().pos.y - theEnemy->GetPaddle().GetSprite().size.y && ballPos.y - theBall->GetSprite().size.y <= theEnemy->GetPaddle().GetSprite().pos.y)
			theBall->FlipVel({ -1.0f, 1.0f });
		else
		{
			playerPoints++;
			ResetLevel();
			mGameState = GameState::PAUSE;
		}
	}
}

void Pong::ResetLevel()
{
	thePlayer->Init();
	theEnemy->Init();
	theBall->Init();

	sprites.push_back(thePlayer->GetPaddle().GetSprite());
	sprites.push_back(theEnemy->GetPaddle().GetSprite());
	sprites.push_back(theBall->GetSprite());
}
void Pong::PrepareSprites()
{
	sprites.clear();
	sprites.push_back(thePlayer->GetPaddle().GetSprite());
	sprites.push_back(theEnemy->GetPaddle().GetSprite());
	sprites.push_back(theBall->GetSprite());
}

void Pong::KeyDown(std::string key)
{
	if (key == "W")
		thePlayer->MoveUp(); 
	if (key == "S")
		thePlayer->MoveDown();
	if (key == "P")
		mGameState = GameState::PAUSE;
	if (key == "Q")
		mGameState = GameState::INGAME;
}

void  Pong::Pause()
{
	if (mGameState == GameState::PAUSE)
		mGameState = GameState::INGAME;

	if (mGameState == GameState::INGAME)
		mGameState = GameState::PAUSE;
}

void Pong::KeyUp(std::string key)
{
	if (key == "W" || key == "S")
		thePlayer->Stop();
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