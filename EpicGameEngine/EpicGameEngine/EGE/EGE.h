#pragma once


#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>


#include "Rendering\Renderers\EBasicRenderer.h"
#include "Rendering\RenderModels\Sprite.h"
#include "Rendering\Shaders\ShaderClasses\EBasicShader.h"
#include "Rendering\Window\Escreen.h"

#include "Util\BasicReader.h"
#include "Util\EGEUtil.h"
#include "Util\GameTimer.h"

using namespace EGE::Util;
using namespace EGE::Shaders;
using namespace EGE::Rendering;
using namespace EGE::Models;
using namespace EGE::Graphics;
using namespace EGE::Math;

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