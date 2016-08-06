#pragma once

#include "IRenderer.h"

using namespace EGE::Content;
namespace EGE { namespace Renderers{
	class EBasicRenderer : public IRenderer
	{
	public:
		void Render(std::vector<Sprite*> sprites)override;

	protected:
		void ICInit()override;
		void ICDestroy()override;

		void Begin()override;
		void Stack(Sprite* spr) override;
		void Flush()override;
	};
}}