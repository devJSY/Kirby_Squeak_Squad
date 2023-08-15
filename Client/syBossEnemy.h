#pragma once
#include "syEnemy.h"

namespace sy
{
	// 상속용 추상클래스
	class BossEnemy : public Enemy
	{
	public:
		BossEnemy(eAbilityType type);
		virtual ~BossEnemy();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other) {};
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) = 0;
		virtual void TakeInhaled(math::Vector2 InhaleDir) {};
		virtual bool IsDamagedState() = 0;
		virtual bool IsDeadState() = 0;
	};
}
