#pragma once
#include "syEnemy.h"

namespace sy
{
	enum class eDaroachState
	{
		Idle,
		Prepare,
		WandUp,
		WandCharge,
		WandAttack,
		BoomAttack,
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

		eDaroachState GetKingDededeState() { return mState; }

	private:
		void CheckPixelCollision();
		void AddStarEffect(eDirection dir);

	private:
		void Idle();
		void Prepare();
		void WandUp();
		void WandCharge();
		void WandAttack();
		void BoomAttack();
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
	};
}
