#pragma once

#include <memory>

#include "..\..\EGE\EGE.h"

using Timestep = float;


#define TICKSPERSECOND 60.f

enum class GameState
{
	MAINMENU,
	INGAME,
	PAUSE
};
class DXApp
{
public:
	DXApp(const HINSTANCE hInstance, const int nShowCmd);

	void Run();

protected:
	virtual void Init() {}
	virtual void Destroy() {}
	
	virtual void Update(const Timestep dt) = 0;
	virtual void Render() = 0;

	virtual void KeyDown(std::string key) {}
	virtual void KeyUp(std::string key) {}
	void InitMessageloop();

protected:
	GameState mGameState;

private:
	std::unique_ptr<EScreen> mScreen;
	std::unique_ptr<GameTimer> mGameTimer;
};