#pragma once
#include "Vector2.h"
#include "Json.h"

namespace sr
{
	struct Transform
	{
		Vector2 pos{ 0.0f,0.0f };
		float rot{ 0.0f };
		float scale{ 1.0f };

		void Read(const json::value_t& value) {
			JSON_READ(value, pos);
			JSON_READ(value, rot);
			JSON_READ(value, scale);

		}
	};
}