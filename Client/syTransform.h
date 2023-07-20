#pragma once
#include "syComponent.h"

namespace sy
{
	using namespace math;

	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize()  override;
		virtual void Update()  override;
		virtual void Render(HDC hdc)  override;

		void SetPosition(Vector2 position) { mPosition = position; }
		Vector2 GetPosition() { return mPosition; }
		void SetRotation(float rotate) { mRotation = rotate; }
		float GetRotation() { return mRotation; }

		eDirection GetDirection() { return mDir; }
		void SetDirection(eDirection dir) { mDir = dir; }

		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() { return mScale; }

	private:
		Vector2 mPosition;
		float	mRotation;
		Vector2 mScale;
		eDirection mDir;
	};
}

