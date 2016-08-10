#pragma once

#include <memory>

#include "../EGE.h"

using Timestep = float;

class DXApp
{
public:
	DXApp(const HINSTANCE hInstance, const int nShowCmd);

	virtual void Init() {}
	void Run();
	virtual void Destroy() {}

protected:
	virtual void Update(const Timestep dt) {}
	virtual void Render() {}
private:
	std::unique_ptr<EScreen> screen{ new EScreen };
};