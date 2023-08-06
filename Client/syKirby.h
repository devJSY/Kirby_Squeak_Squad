#pragma once
#include "syEntity.h"

namespace sy
{
	class Player;
	class Kirby : public Entity
	{
	public:
		Kirby(Player* owner);
		virtual ~Kirby();

		virtual void Initialize();
		virtual void Update();

		virtual void Enter() = 0;
		virtual void Exit() = 0;

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) {};

		virtual void OnCollisionEnter(class Collider* other) {};
		virtual void OnCollisionStay(class Collider* other)	{};
		virtual void OnCollisionExit(class Collider* other) {};

		Player* GetOwner() { return mOwner; }

	private:
		Player* mOwner;
	};
}
