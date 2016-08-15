#pragma once

#include <vector>

#include "IRenderer.h"
#include "../../Util/Math/Vec3f.h"
#include "../../Util/Math/Vec4f.h"
#include "../Shaders/ShaderClasses/EBasicShader.h"

namespace EGE { namespace Rendering{
	
	using namespace Models;
	
	struct Vertex
	{
		Vec3f pos;
		Vec4f colour;
	};

	constexpr int MAXNUMSPRITES{ 40000 }, VERTICESPERSPRITE{ 4 };

	class EBasicRenderer : public IRenderer
	{
	public:
		~EBasicRenderer() {}

		void SetPointLight(const Shaders::PointLight pointLight)const;
	protected:
		void InitializeBuffers()override;
		void InitializeShader()	override;

		void Begin()								override;
		void AddToStack(const Models::Sprite sprite)override;
		void End()									override;

		void Flush(const bool shouldSetBuffers)const override;

		void DeleteShader() override;
	private:
		void InitializeIndexBuffer();

	private:
		int mNumOfSprites;
		
		Vertex* dataPtr;

		std::unique_ptr<Shaders::EBasicShader> mShader{ new Shaders::EBasicShader() };
	};

}}