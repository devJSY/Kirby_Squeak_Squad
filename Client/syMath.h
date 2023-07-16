#pragma once
#include "CommonInclude.h"
#include <cassert>

namespace sy::math
{
	struct Vector2
	{
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

		float x;
		float y;

		Vector2()
			: x(0.0f)
			, y(0.0f)
		{}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{}

		Vector2(UINT _x, UINT _y)
			: x((float)_x)
			, y((float)_y)
		{}

		Vector2(POINT _pt)
			: x((float)_pt.x)
			, y((float)_pt.y)
		{}

		Vector2 operator+(const Vector2 other)
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2& operator+=(const Vector2 other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2 operator-(const Vector2 other)
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator/(const float value)
		{
			assert(!(0.f == x || 0.f == y) || !(0.f == value));
			Vector2 temp;
			temp.x = x / value;
			temp.y = y / value;
			return temp;
		}

		Vector2 operator* (float value)
		{
			return Vector2(x * value, y * value);
		}

		Vector2& operator = (POINT _pt)
		{
			x = (float)_pt.x;
			y = (float)_pt.y;
			return *this;
		}

	};
}
