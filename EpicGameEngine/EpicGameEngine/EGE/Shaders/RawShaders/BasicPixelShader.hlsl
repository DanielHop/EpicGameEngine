struct PixelIn
{
	float4 svPos : SV_POSITION;
	float4 pos : Position;
	float4 colour : Colour;
};

struct AmbientLight
{
	float3 colour;
};

struct PointLight
{
	float range;
	float2 pos;
	float3 colour;
	float2 padding;
};

cbuffer pointLightBuffer : register(b0)
{
	float	PointLightrange;
	float3	PointLightcolour;
	float2	PointLightpos;
	float2	PointLightpadding;
}

float4 main(PixelIn pIn ) : SV_TARGET
{
	float4 retColour = pIn.colour;

	AmbientLight al;
	al.colour = float3(0.2, 0.2, 0.2);
	
	float dist = sqrt((PointLightpos.x - pIn.pos.x) * (PointLightpos.x - pIn.pos.x) + (PointLightpos.y - pIn.pos.y) * (PointLightpos.y - pIn.pos.y));
	float att = 0;
	if(true)
	{
		att = clamp(1.0 - dist*dist / (PointLightrange*PointLightrange), 0.0, 1.0);
		att *= att;
	}
	retColour +=  float4(att * PointLightcolour.x, att * PointLightcolour.y, att * PointLightcolour.z, 0.0);
	//retColour += float4(al.colour, 0.0);
	
	retColour = min(retColour, 1.0);

	return retColour;
}