#pragma once

#include "../../Util/Math/Vec2f.h"
#include "../../Util/Math/Vec3f.h"
#include "../../Util/Math/Vec4f.h"

namespace EGE {	namespace Models {
		struct Sprite
		{
			Math::Vec3f pos;
			Math::Vec2f size;
			Math::Vec4f colour;
		};
}}