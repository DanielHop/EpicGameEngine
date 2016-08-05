#pragma once

#include <memory>

#include "../EGE.h"

class DXApp
{
public:
	DXApp(HINSTANCE hInstance, int nShowCmd);

	virtual void Init() {}
	void Run();
	virtual void Destroy() {}
private:
	std::unique_ptr<ICScreen> screen{ new ICScreen{1280, 720} };
};