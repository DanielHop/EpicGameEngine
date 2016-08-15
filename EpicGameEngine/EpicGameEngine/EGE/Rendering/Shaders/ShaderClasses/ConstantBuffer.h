#pragma once

#include "../../Window/EScreen.h"
#include "../../../Util/Math/Vec4f.h"

using namespace EGE::Math;

namespace EGE { namespace Shaders{
	enum class SHADERKINDS
	{
		PixelShader,
		VertexShader
	};

	struct Buffer
	{
		Vec4f a, b, c, d, e;
	};

	struct BBuffer
	{
		DirectX::XMMATRIX m;
	};
	
	class ConstantBuffer
	{
	public:
		~ConstantBuffer() { Graphics::D3D::ReleaseCom(mCBuffer); }

		void InitBuffer(const UINT size, const SHADERKINDS kind);
		void UpdateBuffer(void* data);
		void SetActiveBuffer(const UINT slot)const;

	private:
		ID3D11Buffer* mCBuffer;
		SHADERKINDS mKind;
		UINT mSize;
	};
}}