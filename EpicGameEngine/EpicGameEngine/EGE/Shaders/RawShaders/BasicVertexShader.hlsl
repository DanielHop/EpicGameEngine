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


VertexOut main( VertexIn vIn )
{
	VertexOut vOut;
	vOut.pos = float4(vIn.pos.x, vIn.pos.y, vIn.pos.z, 1.0);
	vOut.svPos = vOut.pos;
	vOut.colour = vIn.colour;
	return vOut;
}