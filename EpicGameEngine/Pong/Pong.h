#pragma once

#include "Prefabs/DXApp.h"
#include "Entities\Player.h"
#include "Entities\Enemy.h"
#include "Entities\Ball.h"

struct Vertex
{
	float x, y, z;
};


class Pong : public DXApp
{
public:
	Pong(const HINSTANCE hInstance, const int nShowCmd);
	~Pong();

	void Init() override;
	void Destroy()override;

protected:
	void Update(const Timestep dt)override;
	void Render()override;

	void KeyDown(std::string key)override;
	void KeyUp(std::string key)override;

private:
	void PrepareSprites();
	void CollisionCheck();
	void ResetLevel();
	void Pause();
private:
	std::unique_ptr<EBasicRenderer> mRenderer;
	std::unique_ptr<Player> thePlayer;
	std::unique_ptr<Enemy> theEnemy;
	std::unique_ptr<Ball> theBall;

	std::vector<Sprite> sprites;
	
	PointLight p;

	int playerPoints{ 0 }, enemyPoints{ 0 };

	RENDERERS mLastRenderer{ RENDERERS::null };
	SHADERS mLastShader{ SHADERS::null };

};

