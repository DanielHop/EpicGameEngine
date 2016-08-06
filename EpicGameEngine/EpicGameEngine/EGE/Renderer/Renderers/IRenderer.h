#pragma once

#include <vector>

#include "../../Content/IContent.h"
#include "../Models/Sprite.h"

using namespace EGE::Content;
using namespace EGE::Models;


namespace EGE { namespace Renderers{
	class IRenderer : public IContent
	{
	public:
		virtual void Render(std::vector<Sprite*> sprites) = 0;
		
	
	protected:
		virtual void Begin() = 0;
		virtual void Stack(Sprite* spr) = 0;
		virtual void Flush() = 0;

	protected:
		//SHADER PROGRAM
	};
}}