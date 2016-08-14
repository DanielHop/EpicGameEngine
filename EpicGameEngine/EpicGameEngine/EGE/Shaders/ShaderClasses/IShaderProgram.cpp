#include "IShaderProgram.h"

namespace EGE { namespace Shaders{
		void IShaderProgram::SetActive()const
	{
		Graphics::D3D::gDeviceContext->VSSetShader(mVertexShader, NULL, NULL);
		Graphics::D3D::gDeviceContext->PSSetShader(mPixelShader, NULL, NULL);
		Graphics::D3D::gDeviceContext->IASetInputLayout(mInputLayout);
	}

	void IShaderProgram::Init()
	{
		CompileShaders();
		InitializeCBuffers();
	}

	void IShaderProgram::Destroy()
	{
		Graphics::D3D::ReleaseCom(mVertexShader);
		Graphics::D3D::ReleaseCom(mPixelShader);
		Graphics::D3D::ReleaseCom(mInputLayout);
		CleanUpBuffers();
	}

	void IShaderProgram::SetShaderPaths(const std::string VSLocation, const std::string PSLocation)
	{
		mVertexShaderPath = VSLocation;
		mPixelShaderPath = PSLocation;
	}

	void IShaderProgram::CompileShaders()
	{
		auto vertexShaderBuffer = EGE::Util::BasicReader::ReadData(mVertexShaderPath);
		auto pixelShaderBuffer = EGE::Util::BasicReader::ReadData(mPixelShaderPath);
		
		Graphics::D3D::FailCheck(Graphics::D3D::gDevice->CreateVertexShader(vertexShaderBuffer.data(), vertexShaderBuffer.size(), NULL, &mVertexShader), "Creating vertex shader");
		Graphics::D3D::FailCheck(Graphics::D3D::gDevice->CreatePixelShader(pixelShaderBuffer.data() , pixelShaderBuffer.size(), NULL, &mPixelShader),"Creating pixel shader");

		CreateInputLayout(vertexShaderBuffer);
	}
}}