#pragma once
#include "syBossEnemy.h"

namespace sy
{
	enum class eMetaKnightState
	{
		Idle,
		Walk,
		Dash,
		DashAttack,
		Attack1,
		Attack2,
		Jump,
		Turn,
		Drop,
		SpinAttack,
		SparkAttack,
		TornadoAttack,
		Dead,
		End,
	};

	class MetaKnight : public BossEnemy
	{
	public:
		MetaKnight(eAbilityType type);
		virtual ~MetaKnight();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir);
		virtual bool IsDamagedState() { return mbDamaged; }
		virtual bool IsDeadState() { return mState == eMetaKnightState::Dead; }

		eMetaKnightState GeteMetaKnightState() { return mState; }

	private:
		void CheckPixelCollision();
		void AddStarEffect(eDirection dir);

	private:
		void Idle();
		void Walk();
		void Dash();
		void DashAttack();
		void Attack1();
		void Attack2();
		void Jump();
		void Turn();
		void Drop();
		void SpinAttack();
		void SparkAttack();
		void TornadoAttack();
		void Dead();

	private:
		eMetaKnightState	    mState;
		class Animator* mAnimator;
		class Transform* mTransform;
		class Rigidbody* mRigidBody;
		class Collider* mCollider;
		eDirection				mDir;

		float					mStateChangeDelay;
		bool					mbDamaged; // 연속 피격 방지
	};
}




