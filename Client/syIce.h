#pragma once
#include "syEnemy.h"

namespace sy
{
	enum class eIceType
	{
		Small,
		Big
	};

	class Ice : public Enemy
	{
	public:
		Ice(eIceType type);
		virtual ~Ice();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) {};

	private:

	};
}
