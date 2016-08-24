#pragma once

#include "../Prefabs/DXApp.h"
#include "Entities/Player.h"

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

	void Keydown(std::string key)override;
private:
	std::unique_ptr<EBasicRenderer> mRenderer;
	std::unique_ptr<Player> thePlayer;
	std::vector<Sprite> sprites;
	
	PointLight p;

	RENDERERS mLastRenderer{ RENDERERS::null };
	SHADERS mLastShader{ SHADERS::null };

};

