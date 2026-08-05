#pragma once
#include "Vector2.h"

namespace sr
{
	struct Transform
	{
		Vector2 pos{ 0,0 };
		float rotation{ 0.0f };
		float scale{ 1.0f };
	};
}