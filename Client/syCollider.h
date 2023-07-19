#pragma once
#include "syComponent.h"

namespace sy
{
	using namespace math;

	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }

	private:
		Vector2 mSize;
		Vector2 mOffset;
	};
}

