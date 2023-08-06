#pragma once
#include "syEnemy.h"

namespace sy
{
	enum class eIceEnemyType
	{
		Small,
		Big
	};

	class Ice_Enemy : public Enemy
	{
	public:
		Ice_Enemy(eIceEnemyType type);
		virtual ~Ice_Enemy();

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
