#pragma once

#include "IShaderProgram.h"
#include "ConstantBuffer.h"

#include <DirectXMath.h>

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

	struct CBufferPerInstance
	{
		Matrix4f gProjMatrix;
	};

	class EBasicShader : public IShaderProgram
	{
	public:
		EBasicShader(){ SetShaderPaths( "C:/Programming/CPP/EpicGameEngine/EpicGameEngine/Debug/BasicVertexShader.cso" , "C:/Programming/CPP/EpicGameEngine/EpicGameEngine/Debug/BasicPixelShader.cso" ); }
		~EBasicShader() {}
		void SetPointLight(PointLight pl);

	protected:
		void CreateInputLayout(std::vector<uint8_t> vertexShaderBuffer)override;
		void InitializeCBuffers()override;
		void CleanUpBuffers()override;


	private:
		
		std::unique_ptr<ConstantBuffer> mPointLightBuffer;
		std::unique_ptr<ConstantBuffer> mCBufferPerInstance;
	};
}}