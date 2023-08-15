#pragma once
#include "syBossEnemy.h"

namespace sy
{
	enum class eKingDededeState
	{
		Idle,
		Walk,
		JumpReady,
		Jump,
		Drop,
		AttackReady,
		AttackRun,
		Attack,
		FlyReady,
		FlyUp,
		Fly,
		FlyDrop,
		MonsterSummonReady,
		MonsterSummonJump,
		MonsterSummonDrop,
		MonsterSummon,
		Damage,
		Dead,
		End,
	};

	enum class eFlyDiration
	{
		Up,
		Down,
	};

	class KingDedede : public BossEnemy
	{
	public:
		KingDedede(eAbilityType type);
		virtual ~KingDedede();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir);
		virtual bool IsDamagedState() { return mState == eKingDededeState::Damage; }
		virtual bool IsDeadState() { return mState == eKingDededeState::Dead; }

		eKingDededeState GetKingDededeState() { return mState; }

	private:
		void CheckPixelCollision();
		void AddStarEffect(eDirection dir);

	private:
		void Idle();
		void Walk();
		void JumpReady();
		void Jump();
		void Drop();
		void AttackReady();
		void AttackRun();
		void Attack();
		void FlyReady();
		void FlyUp();
		void Fly();
		void FlyDrop();
		void MonsterSummonReady();
		void MonsterSummonJump();
		void MonsterSummonDrop();
		void MonsterSummon();
		void Damage();
		void Dead();

	private:
		eKingDededeState	    mState;
		class Animator*			mAnimator;
		class Transform*		mTransform;
		class Rigidbody*		mRigidBody;
		class Collider*			mCollider;
		eDirection				mDir;
		eFlyDiration			mFlyDir;

		float					mStateChangeDelay;
	};
}
