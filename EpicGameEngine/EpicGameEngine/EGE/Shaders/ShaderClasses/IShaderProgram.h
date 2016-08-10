#pragma once

#include <d3d11.h>

#include "../../Content/IContent.h" 
#include "../../Graphics/EScreen.h"
#include "../../Util/BasicReader.h"

using namespace EGE;

namespace EGE { namespace Shaders{
	class IShaderProgram : public Content::IContent
	{
	public:
		IShaderProgram(const std::string VSLocation, const std::string PSLocation);
		~IShaderProgram();
		void SetActive()const;
	protected:
		void IInit()override;
		void IDestroy()override;

		virtual void CreateInputLayout(std::vector<uint8_t> vertexShaderBuffer) = 0;
		
		void CompileShaders();
	protected:
		std::string					mVertexShaderPath,
									mPixelShaderPath;
		ID3D11VertexShader*			mVertexShader{ nullptr };
		ID3D11PixelShader*			mPixelShader{ nullptr };
		ID3D11InputLayout*			mInputLayout{ nullptr };
	};
}}