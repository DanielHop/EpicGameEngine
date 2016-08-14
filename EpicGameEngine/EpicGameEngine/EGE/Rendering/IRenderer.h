#pragma once

#include <vector>
#include <memory>

#include <d3d11.h>

#include "../Models/Sprite.h"
#include "../Graphics/EScreen.h"

namespace EGE { namespace Rendering {	
	class IRenderer
	{
	public:
		void Prepare(const std::vector<Models::Sprite> sprites);
		void Render(const bool shouldSetBuffers)const;

		void Init();
		void Destroy();
	protected:
		virtual ~IRenderer() {}

		virtual void InitializeBuffers() = 0;
		virtual void InitializeShader() = 0;

		virtual void Begin() = 0;
		virtual void AddToStack(const Models::Sprite sprite) = 0;
		virtual void End() = 0;

		virtual void Flush(const bool shouldSetBuffers)const = 0;

		virtual void DeleteShader() = 0;

		void InitializeDynamicVertexBuffer(const unsigned int byteWidth);

	protected:
		ID3D11Buffer *mVertexBuffer{ nullptr }, *mIndexBuffer{ nullptr };
	};
}}