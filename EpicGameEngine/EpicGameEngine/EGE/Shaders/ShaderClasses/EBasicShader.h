#pragma once

#include "IShaderProgram.h"

#include "../../Models/Vec2f.h"
#include "../../Models/Vec3f.h"
#include "../../Models/Vec4f.h"

using namespace EGE::Models;

namespace EGE { namespace Shaders{

	struct PointLight
	{
		float range;
		Vec3f colour;
		Vec2f pos;
		Vec2f padding;
	};

	struct PointLightBuffer
	{
		PointLight pl;
	};

	class EBasicShader : public IShaderProgram
	{
	public:
		EBasicShader(){ SetShaderPaths( "C:/Programming/CPP/EpicGameEngine/EpicGameEngine/Debug/BasicVertexShader.cso" , "C:/Programming/CPP/EpicGameEngine/EpicGameEngine/Debug/BasicPixelShader.cso" ); }
		~EBasicShader() {}
		void SetPointLight(const PointLight pl);

	protected:
		void CreateInputLayout(std::vector<uint8_t> vertexShaderBuffer)override;
		void InitializeCBuffers()override;
		void CleanUpBuffers()override;


	private:
		ID3D11Buffer* mPointlightBuffer;
	};
}}