#pragma once
#include "CommonInclude.h"
#include <cassert>
#include <cmath>

namespace sy::math
{
#define PI 3.141592f

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

		Vector2 operator -()
		{
			return Vector2(-x, -y);
		}

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

		Vector2& operator -=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Vector2& operator *=(const float& value)
		{
			x *= value;
			y *= value;

			return *this;
		}

		bool operator ==(Vector2 other)
		{
			return (x == other.x && y == other.y);
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

		Vector2 operator/(const Vector2& other)
		{
			assert(!(0.f == x || 0.f == y) || !(0.f == other.x || 0.f == other.y));
			Vector2 temp;
			temp.x = x / other.x;
			temp.y = y / other.y;
			return temp;
		}

		Vector2 operator*(const Vector2& other)
		{
			return Vector2(x * other.x, y * other.y);
		}

		Vector2 operator* (const float& value)
		{
			return Vector2(x * value, y * value);
		}

		Vector2& operator = (POINT _pt)
		{
			x = (float)_pt.x;
			y = (float)_pt.y;
			return *this;
		}

		void clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float Length()
		{
			// c^2 == a^2 + b^2
			return sqrtf(x * x + y * y);
		}

		Vector2 Normalize()
		{
			float len = Length();
			x /= len;
			y /= len;

			return *this;
		}
	};

	inline Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.f) * PI;
		//vector.Normalize(); 원본 벡터의 크기값유지
		float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
		float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

		return Vector2(x, y);
	}

	// 내적
	inline float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	// 외적
	inline float Cross(Vector2 v1, Vector2 v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}
}
