struct VertexIn
{
	float2 pos : Position;
	float4 colour : Colour;
};

struct VertexOut
{
	float4 svPos : SV_POSITION;
	float4 pos : Position;
	float4 colour : Colour;
};

cbuffer CbufferPerInstance : register(b0)
{
	float4x4 gProjMatrix;
}

cbuffer CBufferPerFrame : register(b1)
{
	float4x4 gViewMatrix;
}

cbuffer CBufferPerObject : register(b2)
{
	float4x4 gWorldMatrix;
}

VertexOut main( VertexIn vIn )
{
	VertexOut vOut;
	vOut.pos = mul(gProjMatrix, float4(vIn.pos.x, vIn.pos.y, 1.5, 1.0));
	vOut.svPos = vOut.pos;
	vOut.colour = vIn.colour;
	return vOut;
}