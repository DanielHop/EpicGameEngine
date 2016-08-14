#pragma once

#include <d3d11.h>

#include "../../Graphics/EScreen.h"
#include "../../Util/BasicReader.h"

using namespace EGE;

namespace EGE { namespace Shaders{
	class IShaderProgram
	{
	public:		
		void SetActive()const;

		void Init();
		void Destroy();
	protected:
		virtual ~IShaderProgram() {}

		virtual void CreateInputLayout(std::vector<uint8_t> vertexShaderBuffer) = 0;
		virtual void InitializeCBuffers() = 0;
		virtual void CleanUpBuffers() = 0;

		void SetShaderPaths(const std::string VSLocation, const std::string PSLocation);
		void CompileShaders();
	protected:
		std::string					mVertexShaderPath,
									mPixelShaderPath;
		ID3D11VertexShader*			mVertexShader{ nullptr };
		ID3D11PixelShader*			mPixelShader{ nullptr };
		ID3D11InputLayout*			mInputLayout{ nullptr };
	};
}}