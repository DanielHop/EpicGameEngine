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
	float3 colour;
	float2 pos;
	float2 padding;
};

cbuffer pointLightBuffer : register(b0)
{
	PointLight pointLight;
}

cbuffer CamPos : register(b1)
{
	float2 camPos, padding;
}
float4 main(PixelIn pIn ) : SV_TARGET
{
	float4 retColour = pIn.colour;

	AmbientLight al;
	al.colour = float3(0.2, 0.2, 0.2);
	float corr = 16.f / 9.f;
	float dist = sqrt((pointLight.pos.x - camPos.x - pIn.pos.x * corr) * (pointLight.pos.x - camPos.x - pIn.pos.x * corr ) + (pointLight.pos.y - camPos.y - pIn.pos.y ) * (pointLight.pos.y - camPos.y - pIn.pos.y));
	float att = 0;
		
	att = clamp(1.0 - dist*dist / (pointLight.range*pointLight.range), 0.0, 1.0);
	att *= att;
	
	//retColour *=  float4(att * pointLight.colour.x, att * pointLight.colour.y, att * pointLight.colour.z, 0.0);
	retColour += float4(att * pointLight.colour.x, att * pointLight.colour.y, att * pointLight.colour.z, 0.0);
	//retColour += float4(al.colour, 0.0);
	
	retColour = min(retColour, 1.0);

	return retColour;
}