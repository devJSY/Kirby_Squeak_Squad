#pragma once
#include "syEnemy.h"

namespace sy
{
	enum class eDaroachState
	{
		Idle,
		BombAttackReady,
		BombAttack,
		WandUp,
		WandCharge,
		WandAttack,
		Teleport,
		TeleportEnd,
		StarAttack,
		Damage,
		Dead,
		End,
	};

	class Daroach : public Enemy
	{
	public:
		Daroach(eAbilityType type);
		virtual ~Daroach();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir);
		virtual bool IsDamagedState() { return mState == eDaroachState::Damage; }
		virtual bool IsDeadState() { return mState == eDaroachState::Dead; }

		eDaroachState GetDaroachState() { return mState; }

	private:


	private:
		void Idle();
		void BombAttackReady();
		void BombAttack();
		void WandUp();
		void WandCharge();
		void WandAttack();
		void Teleport();
		void TeleportEnd();
		void StarAttack();
		void Damage();
		void Dead();

	private:
		eDaroachState			 mState;
		class Animator*			 mAnimator;
		class Transform*		 mTransform;
		class Collider*			 mCollider;
		eDirection				 mDir;

		float					 mStateChangeDelay;
		Vector2					 FixedPos[6];
	};
}
