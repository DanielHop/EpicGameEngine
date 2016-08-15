#pragma once

#include "../../Util/Math/Vec2f.h"
#include "../../Util/Math/Vec3f.h"
#include "../../Util/Math/Vec4f.h"

namespace EGE {	namespace Models {
		struct Sprite
		{
			Math::Vec2f pos, size;
			Math::Vec4f colour;

			float rot;
		};
}}