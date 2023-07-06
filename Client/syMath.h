#pragma once

namespace sy::math
{
	struct Vector2
	{
		Vector2()
			: x(0.0f)
			, y(0.0f)
		{}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{}

		float x;
		float y;
	};
}
