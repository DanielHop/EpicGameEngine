#pragma once

#include <d3d11.h>

#include "../../Window/EScreen.h"
#include "../../../Util/BasicReader.h"
#include "../../../Util/Math/Vec2f.h"
#include "../../../Util/Math/Vec3f.h"
#include "../../../Util/Math/Vec4f.h"
#include "../../../Util/Math/Matrix4f.h"
#include "../../../Module/Module.h"

using namespace EGE;
using namespace EGE::Math;

namespace EGE { namespace Shaders{
	
	class IShaderProgram : public Module::Module
	{
	public:		
		void SetActive()const;

	protected:
		virtual ~IShaderProgram() {}

		void LocalInit();
		void LocalDestroy();

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