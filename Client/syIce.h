#pragma once
#include "syEnemy.h"

namespace sy
{
	class Ice : public Enemy
	{
	public:
		Ice();
		virtual ~Ice();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual void TakeHit(int DamageAmount, Vector2 HitDir) override;

	private:
		void CheckPixelCollision();

	private:
	};
}
