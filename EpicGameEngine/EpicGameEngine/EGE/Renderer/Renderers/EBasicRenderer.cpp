#include "EBasicRenderer.h"

using namespace EGE::Renderers;

void EBasicRenderer::ICInit()
{

}

void EBasicRenderer::ICDestroy()
{

}

void EBasicRenderer::Render(std::vector<Sprite*> sprites)
{
	Begin();
	for (auto s : sprites)
		Stack(s);
	Flush();
}

void EBasicRenderer::Begin()
{

}

void EBasicRenderer::Stack(Sprite* spr)
{

}

void EBasicRenderer::Flush()
{

}