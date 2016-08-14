#pragma once

#include "Vec3f.h"
#include "Vec4f.h"

namespace EGE {	namespace Models {
		struct Sprite
		{
			Vec3f pos, size;
			Vec4f colour;
		};
}}