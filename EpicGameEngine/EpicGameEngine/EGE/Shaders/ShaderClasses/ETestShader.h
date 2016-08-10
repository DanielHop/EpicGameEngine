#pragma once

#include "IShaderProgram.h"


namespace EGE { namespace Shaders{
	constexpr char	VertexShaderPath[]{ "C:/Programming/CPP/EpicGameEngine/EpicGameEngine/Debug/BasicVertexShader.cso" }, 
					PixelShaderPath[]{ "C:/Programming/CPP/EpicGameEngine/EpicGameEngine/Debug/BasicPixelShader.cso" };
	class ETestShader : public IShaderProgram
	{
	public:
		ETestShader() : IShaderProgram{VertexShaderPath, PixelShaderPath} {}

		void CreateInputLayout(std::vector<uint8_t> vertexShaderBuffer)override;
	};
}}