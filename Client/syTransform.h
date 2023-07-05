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

	private:
		Vector2 mPosition;
	};
}

