#pragma once


#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>


#include "Rendering\Window\Escreen.h"

#include "Rendering\RenderModels\Sprite.h"

#include "Rendering\Renderers\EBasicRenderer.h"

#include "Rendering\Shaders\ShaderClasses\EBasicShader.h"

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