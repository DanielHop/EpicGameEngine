#include "ETestShader.h"

namespace EGE { namespace Shaders{
	void ETestShader::CreateInputLayout(std::vector<uint8_t> vertexShaderBuffer)
	{
		D3D11_INPUT_ELEMENT_DESC elementDesc[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		Graphics::D3D::FailCheck(Graphics::D3D::gDevice->CreateInputLayout(elementDesc, 1, vertexShaderBuffer.data(), vertexShaderBuffer.size(), &mInputLayout));
	}
}}