#pragma once

#include <memory>

#include "..\..\EGE\EGE.h"

using Timestep = float;

using namespace EGE::Util;
using namespace EGE::Shaders;
using namespace EGE::Rendering;
using namespace EGE::Models;

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

	virtual void Keydown(std::string key) {}
	void InitMessageloop();
private:
	std::unique_ptr<EScreen> screen{ new EScreen };
};