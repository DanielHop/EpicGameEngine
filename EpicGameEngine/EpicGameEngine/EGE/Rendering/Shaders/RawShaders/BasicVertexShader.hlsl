struct VertexIn
{
	float3 pos : Position;
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
	float2 camPos, padding;
}

cbuffer CBufferPerObject : register(b2)
{
	float4x4 gWorldMatrix;
}

VertexOut main( VertexIn vIn )
{
	VertexOut vOut;
	vOut.svPos = mul(gProjMatrix, float4(vIn.pos.x - camPos.x, vIn.pos.y - camPos.y, vIn.pos.z, 1.0));
	vOut.pos = vOut.svPos;
	//vOut.pos = float4(vIn.pos.x, vIn.pos.y, vIn.pos.z, 1.0);
	//vOut.pos = float4(vIn.pos.x - camPos.x, vIn.pos.y - camPos.y, vIn.pos.z, 1.0);
	vOut.colour = vIn.colour;
	return vOut;
}