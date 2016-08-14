#pragma once


#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>


#include "Graphics\EScreen.h"

#include "Models\Sprite.h"

#include "Rendering\EBasicRenderer.h"

#include "Shaders\ShaderClasses\EBasicShader.h"

#include "Util\EGEUtil.h"
#include "Util\BasicReader.h"

using namespace EGE::Graphics;
using namespace EGE::Util;

enum class RENDERERS
{
	EBasicRenderers,
	null,

};

enum class SHADERS
{
	EBasicShader,
	null
};