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
		Vector2 GetPosition() const { return mPosition; }

		void SetRotation(float rotate) { mRotation = rotate; }
		float GetRotation() const { return mRotation; }

		eDirection GetDirection() const { return mDir; }
		void SetDirection(eDirection dir) { mDir = dir; }

	private:
		Vector2 mPosition;
		float	mRotation;
		eDirection mDir;
	};
}

